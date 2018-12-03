/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** main
*/

#include "../../ECS/src/Component/Component.hpp"
#include "../../ECS/src/Entity/Entity.hpp"

class myEntity : public ecs::Entity<myEntity>
{
};

class myComponent : public ecs::Component<myComponent>
{
};

int main()
{
	auto *entity = new myEntity;

	entity->addComponent<myComponent>();

	return 0;
}
