# sl_ovr

A simple reimplementation of Valve's OpenVR loader

## Why?!?

The openvr api library has gotten to me through death by a million cuts. Also, 
I like a good excersie in API design.

## What's different from Valve's?

- Modern CMake structure. Can be added as a subdirectory, or installed in a 
location with exported targets.

- Modern C++ API: RAII and invariants!

- Fewer surprises: For example, you would expect `VR_IsHmdPresent()` to be
extremely lightweight, right? Well, not really. 

- Eager initialization of interfaces. By pre-definining which interfaces will be
used, we get rid of a bunch of thread synchronization and null-checking.

- Lighter footprint. Of particular concern is bringing in a complete json 
library for marginal usage (The current implementation still does, but I plan on 
adding an external json resolver callback in the future).

## Should I use this instead of Valve's?

To be honest, probably not. Especially not for anything that's destined to be 
released commercially.

Specifically, openvr_api relies on a semi-hard-coded path to a config file
containing the location of SteamVR's installation, as well as few pre-defined 
environment variables. This library respects these conventions, but if Valve 
were to change this behavior, they could simply impose an updated  openvr_api.dll 
and back-port all existing titles.

## Usage

```
slt::OVR_context ovr_ctx;

if(ovr_ctx.is_hmd_present()) {
  slt::OVR_system<vr::IVRSystem> sl_vr_system(ovr_ctx, vr::VRApplication_Scene);

  vr::IVRSystem * system = sl_vr_system.get<vr::IVRSystem>();

  //.. carry on as usual
}
```

Obviously, nothing is stopping you from managing the lifetime of `OVR_context` and
`OVR_system` using dynamic allocation. Just keep in mind that `OVR_system`'s 
lifetime must be fully contained within `OVR_context`'s.
