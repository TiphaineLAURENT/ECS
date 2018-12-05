/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** main
*/

#include <iostream>

#include "../../ECS/src/Component/Component.hpp"
#include "../../ECS/src/Entity/EntityManager.hpp"
#include "../../ECS/src/Entity/Entity.hpp"

class myEntity : public ecs::Entity<myEntity>
{
};

class myComponent : public ecs::Component<myComponent>
{
};

int main()
{
	auto entity = ecs::EntityManager::createEntity<myEntity>();

	entity.addComponent<myComponent>();
	entity.addComponent<myComponent>();
	entity.addComponent<myComponent>();
	entity.addComponent<myComponent>();

	std::cout << *static_cast<ecs::IEntity*>(&entity) << std::endl;
	std::cout << *static_cast<ecs::IComponent*>
	(entity.getComponent<myComponent>())
	          << std::endl;

	auto components = entity.getComponents<myComponent>();
	for (auto &component : components) {
		std::cout << *static_cast<ecs::IComponent*>(component)
		          << std::endl;
	}

	auto *entity2 = new myEntity;

	entity2->addComponent<myComponent>();

	std::cout << *static_cast<ecs::IEntity*>(entity2) << std::endl;
	std::cout << *static_cast<ecs::IComponent*>
	(entity2->getComponent<myComponent>())
	          << std::endl;

	return 0;
}
