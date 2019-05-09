add_executable(tests main.cpp ${ECS_SOURCES})
target_link_libraries(tests coverage_config)

add_test(NAME exec_tests COMMAND tests --success)
