cmake_minimum_required(VERSION 2.8.12)
enable_testing()
project(game_text C)
include(CTest)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

link_directories(${CMAKE_SOURCE_DIR})


add_executable(game_text game_text.c)
add_executable(game_test_ymaabout game_test_ymaabout.c)
add_executable(game_test_juruch game_test_juruch.c)
add_executable(game_test_argomes game_test_argomes.c)


target_link_libraries(game_text game)
target_link_libraries(game_test_ymaabout game)
target_link_libraries(game_test_juruch game)



add_test(test_maabout_test_is_over ./game_test_ymaabout test_is_over)
add_test(test_ymaabout_test_game_restart ./game_test_ymaabout test_game_restart)
add_test(test_ymaabout_test_play_move ./game_test_ymaabout test_play_move)
add_test(test_ymaabout_test_check_move ./game_test_ymaabout test_check_move)
add_test(test_ymaabout_test_game_print ./game_test_ymaabout test_game_print)
add_test(test_juruch_dummy ./game_test_juruch dummy)
add_test(test_argomes_dummy ./game_test_argomes dummy)
add_test(test_argomes_game_has_error ./game_test_argomes game_has_error)
