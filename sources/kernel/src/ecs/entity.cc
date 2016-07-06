#include "conurbation/ecs/entity.hh"

namespace Conurbation::ECS
{

    entity_t::~entity_t(){};

    auto entity_t::addComponent(component_t * component, typeid_t tid)->void
    {
        // assert(!hasComponent(tid), u"Already has component")
        component->entity_ = this;
        component->typeid_ = tid;
        component->next_in_entity_ = components_;

        components_ = component;
    }
    auto entity_t::removeComponent(typeid_t tid)->void
    {
        if (components_) {

            if (components_->typeid_ == tid) {
                // Special case where the component to remove is at the head of the list
                auto* _c = components_;
                components_ = components_->next_in_entity_;
                delete _c;
                return;
            }
            else {
                auto* _prev = components_;
                while (_prev->next_in_entity_ && _prev->next_in_entity_->typeid_ != tid)
                    _prev = _prev->next_in_entity_;
                if (_prev->next_in_entity_) {
                    auto* _c = _prev->next_in_entity_;
                    _prev->next_in_entity_ = _prev->next_in_entity_->next_in_entity_;
                    delete _c;
                }
            }
        }
    }
    auto entity_t::getComponent(typeid_t tid)->component_t *
    {
        // Get Component should da a MTF optimization
        if (components_) {
            auto* _c = components_;
            while (true) {
                if (_c->typeid_ == tid)
                    return _c;
                if (_c->next_in_entity_)
                    _c = _c->next_in_entity_;
                else
                    break;
            }
        }
        return nullptr;
    }
    auto entity_t::hasComponent(typeid_t tid)->bool_t
    {
        // Has Component should do a move-to-front optimisation
        if (components_) {
            auto* _c = components_;
            while (true) {
                if (_c->typeid_ == tid)
                    return true;
                if (_c->next_in_entity_)
                    _c = _c->next_in_entity_;
                else
                    break;
            }
        }
        return false;
    }
}
