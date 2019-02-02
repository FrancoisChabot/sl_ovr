#include "sl_ovr/sl_ovr.h"

int main(int argc, const char* argv[]) {
  slt::OVR_context ovr_ctx;

  if(ovr_ctx.is_hmd_present()) {
    slt::OVR_system<vr::IVRSystem> sl_vr_system(ovr_ctx, vr::VRApplication_Scene);

    vr::IVRSystem * system = sl_vr_system.get<vr::IVRSystem>();

    // carry on as usual...
  }

  return 0;
}