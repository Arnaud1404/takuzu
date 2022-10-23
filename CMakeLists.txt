cmake_minimum_required(VERSION 2.6)
enable_testing()
project(game_text C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

link_directories(${CMAKE_SOURCE_DIR})

add_executable(game_text game_text.c)
add_executable(game_test_ymaabout game_test_ymaabout.c)
add_executable(game_test_juruch game_test_juruch.c)
add_executable(game_test_argomes game_test_argomes.c)

target_link_libraries(game_text game)
add_test(test_ymaabout_dummy ./game_test_ymaabout dummy)
add_test(test_juruch_dummy ./game_test_juruch dummy)
add_test(test_argomes_dummy ./game_test_argomes dummy)