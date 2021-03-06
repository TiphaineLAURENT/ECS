/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IComponent
*/

#include "IComponent.hpp"
#include "IEntity.hpp"

namespace ecs
{
        IComponent::IComponent()
        {
                if (!m_freeID.empty())
                {
                        _componentID = m_freeID.back();
                        m_freeID.pop_back();
                        ++m_componentTypeCount;
                }
                else
                {
                        _componentID = m_componentTypeCount++;
                }
        }

        IComponent::~IComponent()
        {
                m_freeID.push_back(_componentID);
                --m_componentTypeCount;
        }

        const size_t &IComponent::get_component_type_count() { return m_componentTypeCount; }

        const ComponentID &IComponent::get_id() const { return _componentID; }

        const EntityID &IComponent::get_owner_id() const { return m_owner->get_id(); }

        IComponent &IComponent::enable()
        {
                _active = true;
                return *this;
        }

        IComponent &IComponent::disable()
        {
                _active = false;
                return *this;
        }

        bool IComponent::is_enabled() const { return _active; }

        IComponent &IComponent::set_owner(NonOwningPointer<IEntity> entity)
        {
                replace_pointer(m_owner, entity);

                return *this;
        }
        NonOwningPointer<IEntity> IComponent::get_owner() const { return m_owner; }

        std::ostream &operator<<(std::ostream &out, const NonOwningPointer<IComponent> component)
        {
                out << "{c "
                    << "ID: " << component->get_id() << ", "
                    << "Count: " << component->get_component_type_count() << ", "
                    << "TypeID: " << component->get_component_type_id() << ", "
                    << "TypeName: " << typeid(component).name() << ", "
                    << "Owner: " << component->get_owner_id() << ", "
                    << "Active: " << component->is_enabled() << true << " }";
                return out;
        }

}    // namespace ecs
