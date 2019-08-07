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


class ENTITY(MyEntity)
{
};

class COMPONENT(MyComponent)
{
};

class COMPONENT(MyComponent2)
{
};

struct SYSTEM(MySystem1)
{
        MySystem1()
                : System(ecs::SYSTEM_PRIORITY::LOWEST)
        {
        }
        void update(long deltaTime) override
        {
                std::cout << deltaTime << " for 1\n";
        }
};

struct SYSTEM(MySystem2)
{
        MySystem2()
                : System(ecs::SYSTEM_PRIORITY::NORMAL, 5)
        {
        }
        void update(long deltaTime) override
        {
                std::cout << deltaTime << " for 2\n";
        }
};

struct SYSTEM(MySystem3)
{
        MySystem3()
                : System(ecs::SYSTEM_PRIORITY::HIGHEST, 1)
        {
        }
        void update(long deltaTime) override
        {
                std::cout << deltaTime << " for 3\n";
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
        REQUIRE(system1.getUpdateInterval() == 10);
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

        systemManager.update(10);
        systemManager.update(5);
        systemManager.update(1);

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
