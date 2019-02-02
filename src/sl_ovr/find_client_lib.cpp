
#include "sl_ovr/errors.h"

#include <fstream>
#include <vector>

#ifndef SL_OVR_EXTERNAL_JSON
#include "json.hpp"
#endif

#if defined(WIN32)
#include <shlobj.h>
#include <windows.h>

#undef GetEnvironmentVariable
#endif

namespace {
std::string get_app_settings_path() {
#if defined(_WIN32)
  char path[MAX_PATH];

  if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE,
                                  NULL, 0, path))) {
    throw slt::Library_load_error();
  }
  return path;
#else
#error "Unsupported platform"
  throw slt::Library_load_error();
#endif
}

std::vector<std::string> get_string_list_from_json(const std::string& contents,
                                                   const std::string& key) {
#ifndef SL_OVR_EXTERNAL_JSON
  std::vector<std::string> result;

  auto as_json = nlohmann::json::parse(contents);
  for (auto& i : as_json.at(key)) {
    result.push_back(i.get<std::string>());
  }
  return result;
#else
  retrun{};
#endif
}

}  // namespace
namespace slt {

namespace detail {
std::string get_default_client_path() {
  auto settings_file = get_app_settings_path() + "/openvr/openvrpaths.vrpath";

  // Alright... this is where we need to load the json file.
  std::ifstream f_stream(settings_file, std::ios::binary);

  if (f_stream) {
    std::string contents;
    f_stream.seekg(0, std::ios::end);
    contents.resize(f_stream.tellg());
    f_stream.seekg(0, std::ios::beg);
    f_stream.read(&contents[0], contents.size());

    auto runtime_paths = get_string_list_from_json(contents, "runtime");

    return runtime_paths[0] + "/bin/vrclient_x64.dll";
  } else {
    throw slt::Library_load_error();
  }
}
}  // namespace detail
}  // namespace slt