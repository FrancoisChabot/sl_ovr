#ifndef _SL_OVR_IFACE_INFOS_H_INCLUDED
#define _SL_OVR_IFACE_INFOS_H_INCLUDED

#include "sl_ovr/openvr_api.h"

namespace slt {

namespace detail {
template <typename T>
struct IFace_info;

template <>
struct IFace_info<vr::IVRSystem> {
  static const char* const version() { return vr::IVRSystem_Version; }
};

template <>
struct IFace_info<vr::IVRChaperone> {
  static const char* const version() { return vr::IVRChaperone_Version; }
};

template <>
struct IFace_info<vr::IVRChaperoneSetup> {
  static const char* const version() { return vr::IVRChaperoneSetup_Version; }
};

template <>
struct IFace_info<vr::IVRCompositor> {
  static const char* const version() { return vr::IVRCompositor_Version; }
};

template <>
struct IFace_info<vr::IVROverlay> {
  static const char* const version() { return vr::IVROverlay_Version; }
};

template <>
struct IFace_info<vr::IVRResources> {
  static const char* const version() { return vr::IVRResources_Version; }
};

template <>
struct IFace_info<vr::IVRRenderModels> {
  static const char* const version() { return vr::IVRRenderModels_Version; }
};

template <>
struct IFace_info<vr::IVRExtendedDisplay> {
  static const char* const version() { return vr::IVRExtendedDisplay_Version; }
};

template <>
struct IFace_info<vr::IVRApplications> {
  static const char* const version() { return vr::IVRApplications_Version; }
};

template <>
struct IFace_info<vr::IVRTrackedCamera> {
  static const char* const version() { return vr::IVRTrackedCamera_Version; }
};

template <>
struct IFace_info<vr::IVRScreenshots> {
  static const char* const version() { return vr::IVRScreenshots_Version; }
};

template <>
struct IFace_info<vr::IVRDriverManager> {
  static const char* const version() { return vr::IVRDriverManager_Version; }
};
}  // namespace detail
}  // namespace slt

#endif