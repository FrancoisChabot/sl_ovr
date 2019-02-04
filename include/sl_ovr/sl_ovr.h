#ifndef _SL_OVR_H_INCLUDED
#define _SL_OVR_H_INCLUDED

#include "sl_ovr/openvr_api.h"

#include "sl_ovr/detail/interface_infos.h"
#include "sl_ovr/detail/shared_lib_utils.h"
#include "sl_ovr/errors.h"

#include <tuple>

namespace vr {
class IVRClientCore;
}

namespace slt {
// OVR_context is responsible for the identification and loading of the
// vr_client dll.
class OVR_context {
 public:
  OVR_context();
  OVR_context(const char* vr_client_path);
  OVR_context(OVR_context&& rhs);
  OVR_context& operator=(OVR_context&& rhs);

  bool is_hmd_present() const;

  ~OVR_context();

 private:
  OVR_context(const OVR_context&) = delete;
  OVR_context& operator=(const OVR_context&) = delete;

  slt::detail::Shared_lib vr_client_lib_;
  vr::IVRClientCore* vr_client_core_ = nullptr;

  friend class OVR_system_base;
  mutable bool system_created_ = false;
};

class OVR_system_base {
 public:
  OVR_system_base(OVR_context& ctx, vr::EVRApplicationType type,
                  const char* info);
  OVR_system_base(OVR_system_base&& rhs);
  OVR_system_base& operator=(OVR_system_base&& rhs);

  ~OVR_system_base();

 protected:
  void* get_interface(const char* version_string);

 private:
  OVR_system_base(const OVR_system_base&) = delete;
  OVR_system_base& operator=(const OVR_system_base&) = delete;

  OVR_context* ctx_ = nullptr;
};

template <typename... Ifaces_t>
class OVR_system : public OVR_system_base {
 public:
  OVR_system(OVR_context& ctx, vr::EVRApplicationType type,
             const char* info = nullptr)
      : OVR_system_base(ctx, type, info) {
    ifaces = std::make_tuple(reinterpret_cast<Ifaces_t*>(
        this->get_interface(detail::IFace_info<Ifaces_t>::version()))...);
  }

  template<typename T>
  operator T*() const {
    return this->get<T>();
  }

  template <typename Iface_t>
  Iface_t* get() const {
    return std::get<Iface_t*>(ifaces);
  }

 private:
  std::tuple<Ifaces_t*...> ifaces;
};
}  // namespace slt

#endif