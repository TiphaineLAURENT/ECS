/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** IEntity
*/

#include "IEntity.hpp"
#include "../Component/ComponentManager.hpp"

namespace ecs
{
        IEntity::IEntity()
        {
                if (!m_freeID.empty())
                {
                        m_entityID = m_freeID.back();
                        m_freeID.pop_back();
                        m_entityCount++;
                }
                else
                {
                        m_entityID = m_entityCount++;
                }
        }

        const EntityID &IEntity::get_id() const { return m_entityID; }

        IEntity &IEntity::enable()
        {
                m_active = true;
                return *this;
        }

        IEntity &IEntity::disable()
        {
                m_active = false;
                return *this;
        }

        bool IEntity::is_enabled() const { return m_active; }

        size_t IEntity::get_entity_count() { return m_entityCount; }

        IEntity::~IEntity() { m_freeID.push_back(m_entityID); }

        std::ostream &operator<<(std::ostream &out, const IEntity *entity)
        {
                out << "{e "
                    << "ID: " << entity->get_id() << ", "
                    << "Entity count: " << entity->get_entity_count() << ", "
                    << "Entity type ID: " << entity->get_entity_type_id() << ", "
                    << "Entity type name: " << typeid(entity).name() << " }";

                return out;
        }

}    // namespace ecs
