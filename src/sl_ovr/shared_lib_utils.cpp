// This is taken almost verbatim from Valve's
// openvr/src/vrcommon/sharedlibtools_public.cpp

#include "sl_ovr/detail/shared_lib_utils.h"
#include "sl_ovr/errors.h"

#include <cassert>

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace slt {
namespace detail {
Shared_lib::Shared_lib(const char* path) {
#if defined(_WIN32)
  handle_ = LoadLibraryEx(path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#else
  handle_ = dlopen(path, RTLD_LOCAL | RTLD_NOW);
#endif

  if (!handle_) {
    throw Library_load_error();
  }
}

Shared_lib::Shared_lib(Shared_lib&& rhs) : handle_(rhs.handle_) {
  rhs.handle_ = nullptr;
}

Shared_lib& Shared_lib::operator=(Shared_lib&& rhs) {
  handle_ = rhs.handle_;
  rhs.handle_ = nullptr;
  return *this;
}

Shared_lib::~Shared_lib() {
  if (handle_) {
#if defined(_WIN32)
    FreeLibrary((HMODULE)handle_);
#else
    dlclose(handle_);
#endif
  }
}

void* Shared_lib::get_symbol_ptr_(const char* name) const {
  void* result = nullptr;

#if defined(_WIN32)
  result = (void*)GetProcAddress((HMODULE)handle_, name);
#else
  result = dlsym(handle_, pchFunctionName);
#endif

  if (!result) {
    throw Function_lookup_error();
  }

  return result;
}
}  // namespace detail
}  // namespace slt
