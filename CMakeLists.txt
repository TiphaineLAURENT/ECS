cmake_minimum_required(VERSION 3.14)
project(ECS)
set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_NAME "Starfarm")


set(ECS_SOURCE_DIRECTORY ECS/src)
set(ECS_SOURCES
    ECS/src/Entity/IEntity.cpp ECS/src/Entity/IEntity.hpp
    ECS/src/util/util.hpp
    ECS/src/Component/ComponentManager.cpp ECS/src/Component/ComponentManager.hpp
    ECS/src/Component/ComponentContainer.cpp ECS/src/Component/ComponentContainer.hpp
    ECS/src/Component/IComponent.cpp ECS/src/Component/IComponent.hpp
    ECS/src/Entity/Entity.cpp ECS/src/Entity/Entity.hpp
    ECS/src/Component/Component.cpp ECS/src/Component/Component.hpp
    ECS/src/Component/IComponentContainer.cpp ECS/src/Component/IComponentContainer.hpp
    ECS/src/Entity/EntityManager.cpp ECS/src/Entity/EntityManager.hpp
    ECS/src/Entity/IEntityContainer.cpp ECS/src/Entity/IEntityContainer.hpp
    ECS/src/Entity/EntityContainer.cpp ECS/src/Entity/EntityContainer.hpp
    ECS/src/System/ISystem.cpp ECS/src/System/ISystem.hpp
    ECS/src/System/System.cpp ECS/src/System/System.hpp
    ECS/src/System/SystemManager.cpp ECS/src/System/SystemManager.hpp
    ECS/src/System/SimpleSystemManager.cpp ECS/src/System/SimpleSystemManager.hpp
    ECS/src/System/MediumSystemManager.cpp ECS/src/System/MediumSystemManager.hpp
    )

list(SORT ECS_SOURCES COMPARE FILE_BASENAME)
list(TRANSFORM ECS_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(JOIN ECS_SOURCES "\n" ECS_SOURCES_STRING)
message("Found ecs sources: [\n" ${ECS_SOURCES_STRING} "\n]")

add_library(ecs STATIC ${ECS_SOURCES})
add_library(ecs_shared SHARED ${ECS_SOURCES})

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
