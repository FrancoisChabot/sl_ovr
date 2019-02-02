#include "sl_ovr/errors.h"
#include "sl_ovr/ivrclientcore.h"

namespace slt {

::vr::IVRClientCore* VR_init_error::runtime_ = nullptr;

namespace detail {
const char* get_error_string(vr::EVRInitError e, ::vr::IVRClientCore* runtime) {
  if (runtime) {
    return runtime->GetEnglishStringForHmdError(e);
  }
  // We "could" maintain a string table here.
  return "early init error";
}
}  // namespace detail

Library_load_error::Library_load_error()
    : std::runtime_error("Failed to load library") {}

Function_lookup_error::Function_lookup_error()
    : std::runtime_error("Failed to lookup function") {}

VR_init_error::VR_init_error(const char* what) : std::runtime_error(what) {}

VR_init_error::VR_init_error(vr::EVRInitError e)
    : error(e), std::runtime_error(detail::get_error_string(e, runtime_)) {}

}  // namespace slt
