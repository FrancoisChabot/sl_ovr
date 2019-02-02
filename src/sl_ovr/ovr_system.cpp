#include "sl_ovr/sl_ovr.h"

#include "sl_ovr/errors.h"
#include "sl_ovr/ivrclientcore.h"

#include <cassert>
#include <string>

namespace slt {

OVR_system_base::OVR_system_base(OVR_context& ctx, vr::EVRApplicationType type,
                                 const char* info)
    : ctx_(&ctx) {
  if (ctx_->system_created_) {
    throw VR_init_error("Cannot have multiple Systems at once.");
  }

  auto status = ctx_->vr_client_core_->Init(type, info);

  if (status != vr::VRInitError_None) {
    throw VR_init_error(status);
  }

  status =
      ctx_->vr_client_core_->IsInterfaceVersionValid(vr::IVRSystem_Version);
  if (status != vr::VRInitError_None) {
    throw VR_init_error(status);
  }

  ctx_->system_created_ = true;
}

OVR_system_base::OVR_system_base(OVR_system_base&& rhs) : ctx_(rhs.ctx_) {
  rhs.ctx_ = nullptr;
}

OVR_system_base& OVR_system_base::operator=(OVR_system_base&& rhs) {
  ctx_ = rhs.ctx_;

  rhs.ctx_ = nullptr;
  return *this;
}

OVR_system_base::~OVR_system_base() {
  if (ctx_) {
    assert(ctx_->system_created_);
    ctx_->system_created_ = false;
  }
}

void* OVR_system_base::get_interface(const char* version_string) {
  vr::EVRInitError status;
  void* result =
      ctx_->vr_client_core_->GetGenericInterface(version_string, &status);

  if (status != vr::VRInitError_None) {
    throw VR_init_error(status);
  }
  return result;
}
}  // namespace slt