#ifndef _SL_OVR_ERRORS_H_INCLUDED
#define _SL_OVR_ERRORS_H_INCLUDED

#include <stdexcept>

#include "sl_ovr/openvr_api.h"

namespace vr {
class IVRClientCore;
}

namespace slt {

class Library_load_error : public std::runtime_error {
 public:
  Library_load_error();
};

class Function_lookup_error : public std::runtime_error {
 public:
  Function_lookup_error();
};

class VR_init_error : public std::runtime_error {
 public:
  VR_init_error(const char* what);
  VR_init_error(::vr::EVRInitError e);

 private:
  ::vr::EVRInitError error = ::vr::VRInitError_Unknown;

  friend class OVR_context;
  static ::vr::IVRClientCore* runtime_;
};
}  // namespace slt

#endif