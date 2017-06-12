# Jones

Jones is a framework for loading and running non-PE/COFF images from within the
UEFI Pre-Boot Environment.

Jones only adapts the image format, not the ABI. You still need to provide an
entry point compatible with the UEFI ABI.

## Binaries

This module produces two EFI binaries

### `jonessvc.efi`

This is an UEFI Boot Service Driver which provides the Jones infrastructure.

### `jones.efi`

This is a stub application which connects to the Jones driver and uses it to
load and run an executable image.

## How it Works

On the client-side (i.e. jones.efi) it works like this...

  * The client acquires the Jones Protocol which has GUID
    `a9cc669b-2e3c-471d-b300-df05883c3015`.
  * The client materializes an EFI_DEVICE_PATH which points to the image to be
    loaded.
  * The client calls the GetLoader function on the Jones Protocol with the
    device path. This materializes the Jones Loadable Protocol on the underlying
    handle, which has GUID `851964ce-c8c3-4ae0-aac9-b2895fc68a2f`.
  * The client calls LoadRun on the Jones Loadable Protocol instance. An image
    handle is created with the Jones Loaded Image Protocol attached, and the
    client's image handle as parent. This is passed to the entry point of the
    image.

On the driver side, at initialization time

  * The driver creates a single instance of the Jones Protocol with GUID
    `a9cc669b-2e3c-471d-b300-df05883c3015` and attached it to it's image handle.
  * The driver creates a number of instances of Jones Loader Protocol with GUID
    `89cfa780-1d79-434b-9efb-52d6a87f701c` and attaches them to new handles.

When the client calls GetLoader

  * The driver opens an instance of EFI File Protocol for the given path
  * The driver enumerates all installed instances of Jones Loader Protocol in
    the system, calling the CanLoad function on each with the open file
  * On the first match, the driver will call PrepareLoad on the Jones Loader
    Protocol. This materializes an instance of Jones Loadable Protocol and
    attaches it to the File Handle.

### Isn't four protocols rather a lot?

It makes it extensible.

  * **Jones Protocol** is the singleton entry point to the Jones infrastructure.
  * **Jones Loader Protocol** implements the per-format part of the driver
  * **Jones Loadable Protocol** is attached to a file once the format and
    appropriate loading routines have been identified.
  * **Jones Loaded Image Protocol** is attached to the loaded image's handle and
    allows it to reflect on it's load process from within it's entry point.

Any UEFI Boot Service Driver can create additional instances of Jones Loader
Protocol to support additional formats.

### Why this client/driver split?

It seems neater. Also I have ideas about EFI Applications and Boot Loaders (and
even kernels before they ExitBootServices) using it.
