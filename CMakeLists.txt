cmake_minimum_required(VERSION 2.8.12)
enable_testing()
project(game_text C)
include(CTest)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

link_directories(${CMAKE_SOURCE_DIR})


add_executable(game_text game_text.c)
add_executable(game_test_ymaabout game_test_ymaabout.c)
add_executable(game_test_juruch game_test_juruch.c)



target_link_libraries(game_text game)
target_link_libraries(game_test_ymaabout game)
target_link_libraries(game_test_juruch game)



add_test(test_ymaabout_test_is_over ./game_test_ymaabout test_is_over)
add_test(test_ymaabout_test_game_restart ./game_test_ymaabout test_game_restart)
add_test(test_ymaabout_test_play_move ./game_test_ymaabout test_play_move)
add_test(test_ymaabout_test_check_move ./game_test_ymaabout test_check_move)
add_test(test_ymaabout_test_game_print ./game_test_ymaabout test_game_print)
add_test(test_juruch_test_dummy ./game_test_juruch test_dummy)
add_test(test_juruch_test_game_new_empty ./game_test_juruch test_game_new_empty)
add_test(test_juruch_test_game_delete ./game_test_juruch test_game_delete)
add_test(test_juruch_test_game_set_square ./game_test_juruch test_game_set_square)
add_test(test_juruch_test_game_get_next_square ./game_test_juruch test_game_get_next_square)
add_test(test_juruch_test_game_default ./game_test_juruch test_game_default)
add_test(test_juruch_test_game_default_solution ./game_test_juruch test_game_default_solution)



