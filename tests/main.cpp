//
// Created by TipLa on 13/04/2019.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include <Entity.hpp>
#include <EntityManager.hpp>
#include <Component.hpp>
#include <ComponentManager.hpp>
#include <System.hpp>
#include <SystemManager.hpp>


class MyEntity
        : public ecs::Entity<MyEntity>
{
};

class MyComponent
        : public ecs::Component<MyComponent>
{
};

class MyComponent2
        : public ecs::Component<MyComponent2>
{
};

class MySystem
        : public ecs::System<MySystem>
{
};

TEST_CASE("Basic creation", "creation")
{
        auto entity = ecs::EntityManager::createEntity<MyEntity>();
        REQUIRE(ecs::EntityManager::getEntityContainer<MyEntity>()
                        .getEntityContainerTypeName()
                == typeid(MyEntity).name());
        REQUIRE(entity.getEntityCount() == 1);
        REQUIRE(entity.getEntityID() == 0);
        REQUIRE(entity.getEntityTypeID() == 0);

        auto &system = ecs::SystemManager::createSystem<MySystem>();

        REQUIRE(system.getPriority() == ecs::SystemPriority::NORMAL);
        REQUIRE(system.getSystemTypeID() == 0);
        REQUIRE(system.getUpdateInterval() == 1.);
        REQUIRE(system.isEnable());

        REQUIRE(entity.addComponent<MyComponent>() != nullptr);
        auto component = entity.getComponent<MyComponent>();

        REQUIRE(ecs::ComponentManager::getInstance().getContainerCount() == 1);
        REQUIRE(component->getComponentCount() == 1);
        REQUIRE(component->getComponentTypeCount() == 1);
        REQUIRE(component->getComponentID() == 0);
        REQUIRE(component->getComponentTypeID() == 0);
        REQUIRE(component->isActive());
        REQUIRE(component->getOwner() == entity.getEntityID());

        REQUIRE(ecs::ComponentManager::getComponentContainer<MyComponent>()
                        .getComponentContainerTypeName()
                == typeid(MyComponent).name());

        auto component2 = entity.addComponent<MyComponent2>();
        REQUIRE(ecs::ComponentManager::getInstance().getContainerCount() == 2);
        REQUIRE(component->getComponentCount() == 2);
        REQUIRE(component->getComponentTypeCount() == 1);
        REQUIRE(component->getComponentID() == 1);
        REQUIRE(component->getComponentTypeID() == 1);
        REQUIRE(!component2->setActive(false).isActive());

        entity.removeComponent<MyComponent2>();
        REQUIRE(component->getComponentCount() == 1);

        REQUIRE(!entity.setActive(false).isActive());
        ecs::EntityManager::removeEntity<MyEntity>(entity.getEntityID());
}
