#include "conurbation/guid.hh"
#include "jones/jones.hh"
#include "jones/jones_loaded_image.hh"
#include "jones/jones_loader.hh"
#include "jones/jones.hh"


template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loader_p> [[gnu::weak]] = "89cfa780-1d79-434b-9efb-52d6a87f701c"_guid;
template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_p> [[gnu::weak]] = "a9cc669b-2e3c-471d-b300-df05883c3015"_guid;
template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loaded_image_p> [[gnu::weak]] = "84e62bd3-32f7-46b7-b312-cb3dbf90fda8"_guid;
template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loadable_p> [[gnu::weak]] = "851964ce-c8c3-4ae0-aac9-b2895fc68a2f"_guid;
