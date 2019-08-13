add_executable(tests main.cpp ${ECS_SOURCES})
target_link_libraries(tests coverage_config)

include_directories(${CMAKE_SOURCE_DIR}/ECS/src/Entity)
include_directories(${CMAKE_SOURCE_DIR}/ECS/src/Component)
include_directories(${CMAKE_SOURCE_DIR}/ECS/src/System)
add_test(NAME exec_tests COMMAND tests --success)
