//
// Created by TipLa on 13/04/2019.
//

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_DISABLE_EXCEPTIONS

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

class DerivedComponent : public MyComponent
{};

class COMPONENT(MyComponent2)
{
};

struct SYSTEM(MySystem1)
{
        MySystem1()
                : System(ecs::SYSTEM_PRIORITY::LOWEST)
        {
        }
        void update(ecs::Interval deltaTime) override
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
        void update(ecs::Interval deltaTime) override
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
        void update(ecs::Interval deltaTime) override
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

        systemManager.update(10); // 10 us passed
        systemManager.update(5);  // 15 us passed
        systemManager.update(1);  // 16 us passed
        systemManager.update(1);  // 17 us passed
        systemManager.update(1);  // 18 us passed
        systemManager.update(1);  // 19 us passed
        systemManager.update(1);  // 20 us passed

        REQUIRE(entity.addComponent<MyComponent>() != nullptr);
        auto component = entity.getComponent<MyComponent>();

        REQUIRE(ecs::ComponentManager::getInstance().getContainerCount() == 1);
        REQUIRE(component->getComponentCount() == 1);
        REQUIRE(component->getComponentTypeCount() == 1);
        REQUIRE(component->getComponentID() == 0);
        REQUIRE(component->getComponentTypeID() == 0);
        REQUIRE(component->isActive());
        REQUIRE(component->getOwnerId() == entity.getEntityID());

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

        auto derived = ecs::ComponentManager::addComponent<DerivedComponent, MyComponent>(&entity);
        REQUIRE(ecs::ComponentManager::getComponents<MyComponent>(entity.getEntityID()).size() == 2);

        entity.removeComponent<MyComponent2>();
        REQUIRE(component->getComponentCount() == 2);

        REQUIRE(!entity.setActive(false).isActive());
        ecs::EntityManager::removeEntity<MyEntity>(entity.getEntityID());
}
