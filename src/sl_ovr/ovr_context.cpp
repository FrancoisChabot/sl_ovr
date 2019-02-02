#include "sl_ovr/sl_ovr.h"

#include "sl_ovr/errors.h"
#include "sl_ovr/ivrclientcore.h"

#include <cassert>
#include <string>

namespace slt {

namespace detail {
std::string get_default_client_path();
}

namespace {
constexpr const char* client_core_factory_name = "VRClientCoreFactory";
using core_factory_fn = void* (*)(const char* pInterfaceName, int* pReturnCode);
}  // namespace

OVR_context::OVR_context()
    : OVR_context(detail::get_default_client_path().c_str()) {}

OVR_context::OVR_context(const char* vr_client_path)
    : vr_client_lib_(vr_client_path) {
  auto core_factory =
      vr_client_lib_.get_symbol<core_factory_fn>(client_core_factory_name);

  int status = 0;  // This is a mistery to me...
  vr_client_core_ = reinterpret_cast<vr::IVRClientCore*>(
      core_factory(vr::IVRClientCore_Version, &status));

  if (!vr_client_core_) {
    throw VR_init_error("Failed to create client core");
  }

  VR_init_error::runtime_ = vr_client_core_;
}

OVR_context::OVR_context(OVR_context&& rhs)
    : vr_client_lib_(std::move(rhs.vr_client_lib_)),
      vr_client_core_(rhs.vr_client_core_) {
  rhs.vr_client_core_ = nullptr;
}

OVR_context& OVR_context::operator=(OVR_context&& rhs) {
  vr_client_lib_ = std::move(rhs.vr_client_lib_);
  vr_client_core_ = rhs.vr_client_core_;

  rhs.vr_client_core_ = nullptr;
  return *this;
}

bool OVR_context::is_hmd_present() const {
  assert(vr_client_core_);
  return vr_client_core_->BIsHmdPresent();
}

OVR_context::~OVR_context() {
  if (vr_client_core_) {
    assert(!system_created_);
    VR_init_error::runtime_ = nullptr;
    vr_client_core_->Cleanup();
  }
}
}  // namespace slt