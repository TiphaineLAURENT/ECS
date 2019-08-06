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
#include <MediumSystemManager.hpp>


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

struct MySystem1
        : public ecs::System<MySystem1>
{
        MySystem1()
                : System(ecs::SYSTEM_PRIORITY::LOWEST)
        {
        }
};

struct MySystem2
        : public ecs::System<MySystem2>
{
        MySystem2()
                : System(ecs::SYSTEM_PRIORITY::NORMAL)
        {
        }
};

struct MySystem3
        : public ecs::System<MySystem3>
{
        MySystem3()
                : System(ecs::SYSTEM_PRIORITY::HIGHEST)
        {
        }
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

        auto systemManager = ecs::MediumSystemManager();
        auto &system1 = systemManager.createSystem<MySystem1>();
        REQUIRE(system1.getPriority() == ecs::SYSTEM_PRIORITY::LOWEST);
        REQUIRE(system1.getSystemTypeID() == 0);
        REQUIRE(system1.getUpdateInterval() == 1.);
        REQUIRE(system1.isEnable());

        auto &system2 = systemManager.createSystem<MySystem2>();
        auto &system3 = systemManager.createSystem<MySystem3>();
        systemManager.updateSytemsOrder();
        REQUIRE(systemManager[0]->getPriority() ==
                ecs::SYSTEM_PRIORITY::HIGHEST);
        REQUIRE(systemManager[1]->getPriority() ==
                ecs::SYSTEM_PRIORITY::NORMAL);
        REQUIRE(systemManager[2]->getPriority() ==
                ecs::SYSTEM_PRIORITY::LOWEST);

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
        REQUIRE(component->getComponentID() == 0);
        REQUIRE(component->getComponentTypeID() == 0);

        REQUIRE(component2->getComponentCount() == 2);
        REQUIRE(component2->getComponentTypeCount() == 1);
        REQUIRE(component2->getComponentID() == 1);
        REQUIRE(component2->getComponentTypeID() == 1);
        REQUIRE(!component2->setActive(false).isActive());

        entity.removeComponent<MyComponent2>();
        REQUIRE(component->getComponentCount() == 1);

        REQUIRE(!entity.setActive(false).isActive());
        ecs::EntityManager::removeEntity<MyEntity>(entity.getEntityID());
}
