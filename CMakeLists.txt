cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CMAKE_CXX_STANDARD  17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

set(ECS_SOURCE_DIRECTORY ECS/src)
set(ECS_SOURCES
        ECS/src/ECS.cpp ECS/src/ECS.hpp
        ECS/src/Entity/Entity.cpp ECS/src/Entity/Entity.hpp ECS/src/Component/IComponentContainer.hpp ECS/src/Component/IComponent.hpp ECS/src/Platform.hpp ECS/src/Entity/IEntity.hpp ECS/src/Component/ComponentManager.cpp ECS/src/Component/ComponentManager.hpp)
add_library(ECS SHARED ${ECS_SOURCES})

add_executable(test test/src/main.cpp)

set_target_properties(ECS PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(test ECS)
