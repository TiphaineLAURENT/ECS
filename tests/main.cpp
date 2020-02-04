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
        auto entity = ecs::EntityManager::create<MyEntity>();
        REQUIRE(ecs::EntityManager::get_entity_container<MyEntity>()
                        .get_entity_type_name()
                == typeid(MyEntity).name());
        REQUIRE(entity.get_entity_count() == 1);
        REQUIRE(entity.get_id() == 0);
        REQUIRE(entity.get_entity_type_id() == 0);

        auto systemManager = ecs::MediumSystemManager();
        auto &system1 = systemManager.create_system<MySystem1>();
        REQUIRE(system1.get_priority() == ecs::SYSTEM_PRIORITY::LOWEST);
        REQUIRE(system1.get_system_type_id() == 0);
        REQUIRE(system1.get_update_interval() == 10);
        REQUIRE(system1.is_enabled());

        auto &system2 = systemManager.create_system<MySystem2>();
        auto &system3 = systemManager.create_system<MySystem3>();
        systemManager.update_systems_order();
        REQUIRE(systemManager[0]->get_priority() ==
                ecs::SYSTEM_PRIORITY::HIGHEST);
        REQUIRE(systemManager[1]->get_priority() ==
                ecs::SYSTEM_PRIORITY::NORMAL);
        REQUIRE(systemManager[2]->get_priority() ==
                ecs::SYSTEM_PRIORITY::LOWEST);

        systemManager.update(10); // 10 us passed
        systemManager.update(5);  // 15 us passed
        systemManager.update(1);  // 16 us passed
        systemManager.update(1);  // 17 us passed
        systemManager.update(1);  // 18 us passed
        systemManager.update(1);  // 19 us passed
        systemManager.update(1);  // 20 us passed

        REQUIRE(entity.create_component<MyComponent>() != nullptr);
        auto component = entity.get_component<MyComponent>();

        REQUIRE(ecs::ComponentManager::get_instance().get_container_count() == 1);
        REQUIRE(component->get_component_count() == 1);
        REQUIRE(component->get_id() == 0);
        REQUIRE(component->get_component_type_id() == 0);
        REQUIRE(component->is_enabled());
        REQUIRE(component->get_owner() == &entity);
        REQUIRE(component->get_owner()->get_id() == entity.get_id());
        REQUIRE(component->get_owner_id() == entity.get_id());

        REQUIRE(ecs::ComponentManager::get_component_container<MyComponent>()
                        .get_component_type_name()
                == typeid(MyComponent).name());

        auto component2 = entity.create_component<MyComponent2>();
        REQUIRE(ecs::ComponentManager::get_instance().get_container_count() == 2);
        REQUIRE(component->get_component_type_count() == 2);
        REQUIRE(component->get_component_count() == 1);
        REQUIRE(component->get_id() == 0);
        REQUIRE(component->get_component_type_id() == 0);

        REQUIRE(component2->get_component_type_count() == 2);
        REQUIRE(component2->get_component_count() == 1);
        REQUIRE(component2->get_id() == 1);
        REQUIRE(component2->get_component_type_id() == 1);
        REQUIRE(!component2->disable().is_enabled());

        auto derived = entity.create_component<DerivedComponent, MyComponent>();
        REQUIRE(ecs::ComponentManager::get_components<MyComponent>(entity.get_id()).size() == 2);

        entity.erase_component<MyComponent2>();
        REQUIRE(component->get_component_count() == 2);

        REQUIRE(!entity.disable().is_enabled());
        ecs::EntityManager::remove_entity<MyEntity>(entity.get_id());
}
