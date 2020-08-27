/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

namespace ecs
{
        EntityManager &EntityManager::get_instance()
        {
                static EntityManager instance;
                return instance;
        }

        template <IsEntity E> CComponentIterator<E> EntityManager::begin()
        {
                return get_entity_container<E>().begin();
        }

        template <IsEntity E> CComponentIterator<E> EntityManager::end()
        {
                return get_entity_container<E>().begin();
        }

}    // namespace ecs
