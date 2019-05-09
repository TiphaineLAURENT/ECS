cmake_minimum_required(VERSION 3.10)
project(Starfarm)
set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_NAME "Starfarm")


set(ECS_SOURCE_DIRECTORY ECS/src)
set(ECS_SOURCES
    ${CMAKE_SOURCE_DIR}/ECS/src/Entity/IEntity.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Entity/IEntity.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/util/util.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Component/ComponentManager.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Component/ComponentManager.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Component/ComponentContainer.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Component/ComponentContainer.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Component/IComponent.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Component/IComponent.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Entity/Entity.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Entity/Entity.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Component/Component.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Component/Component.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Component/IComponentContainer.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Component/IComponentContainer.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Entity/EntityManager.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Entity/EntityManager.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Entity/IEntityContainer.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Entity/IEntityContainer.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/Entity/EntityContainer.cpp ${CMAKE_SOURCE_DIR}/ECS/src/Entity/EntityContainer.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/System/ISystem.cpp ${CMAKE_SOURCE_DIR}/ECS/src/System/ISystem.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/System/System.cpp ${CMAKE_SOURCE_DIR}/ECS/src/System/System.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/System/SystemManager.cpp ${CMAKE_SOURCE_DIR}/ECS/src/System/SystemManager.hpp
    ${CMAKE_SOURCE_DIR}/ECS/src/System/SimpleSystemManager.cpp ${CMAKE_SOURCE_DIR}/ECS/src/System/SimpleSystemManager.hpp
    )
add_library(ecs STATIC ${ECS_SOURCES})

include_directories(ECS/src/Entity)
include_directories(ECS/src/Component)
include_directories(ECS/src/System)

add_library(coverage_config INTERFACE)
option(CODE_COVERAGE "Enable coverage reporting" OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(coverage_config INTERFACE
                           -O0
                           -g
                           --coverage
                           )
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else ()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif ()
endif ()

option(BUILD_TESTING "Build testing tree" ON)
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory(tests)
endif ()
