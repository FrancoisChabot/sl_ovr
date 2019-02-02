// This is heavily inspired from Valve's
// openvr/src/vrcommon/sharedlibtools_public.h

#ifndef _SL_OVR_SHARED_LIB_UTILS_H_INCLUDED
#define _SL_OVR_SHARED_LIB_UTILS_H_INCLUDED

#include <string>

namespace slt {
namespace detail {
class Shared_lib {
 public:
  Shared_lib(const char* path);
  ~Shared_lib();

  Shared_lib(Shared_lib&& rhs);
  Shared_lib& operator=(Shared_lib&& rhs);

  template <typename T>
  T get_symbol(const char* name) const {
    return reinterpret_cast<T>(get_symbol_ptr_(name));
  }

  template <typename T>
  void get_symbol(const char* name, T& dst) const {
    dst = get_symbol<T>(name);
  }

 private:
  Shared_lib(const Shared_lib&) = delete;
  Shared_lib& operator=(const Shared_lib&) = delete;

  void* handle_ = nullptr;

  void* get_symbol_ptr_(const char* name) const;
};
}  // namespace detail
}  // namespace slt

#endif