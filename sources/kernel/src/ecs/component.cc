#include "conurbation/ecs/component.hh"

namespace Conurbation::ECS
{
    typeid_t TypeId::next_typeid__ = 1;

    component_t::~component_t(){};
}
