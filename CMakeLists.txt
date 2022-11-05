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
target_link_libraries(game_test_argomes game)

add_test(test_ymaabout_test_dummy ./game_test_ymaabout dummy)
add_test(test_ymaabout_test_is_over ./game_test_ymaabout is_over)
add_test(test_ymaabout_test_game_restart ./game_test_ymaabout game_restart)
add_test(test_ymaabout_test_play_move ./game_test_ymaabout play_move)
add_test(test_ymaabout_test_check_move ./game_test_ymaabout check_move)
add_test(test_ymaabout_test_game_print ./game_test_ymaabout game_print)

add_test(test_juruch_test_dummy ./game_test_juruch dummy)
add_test(test_juruch_test_game_new_empty ./game_test_juruch game_new_empty)
add_test(test_juruch_test_game_delete ./game_test_juruch game_delete)
add_test(test_juruch_test_game_set_square ./game_test_juruch game_set_square)
add_test(test_juruch_test_game_get_next_square ./game_test_juruch game_get_next_square)
add_test(test_juruch_test_game_default ./game_test_juruch game_default)
add_test(test_juruch_test_game_default_solution ./game_test_juruch game_default_solution)

add_test(test_argomes_test_dummy ./game_test_argomes dummy)
add_test(test_argomes_test_game_has_error ./game_test_argomes game_has_error)
add_test(test_argomes_test_game_copy ./game_test_argomes game_copy)
add_test(test_argomes_test_game_is_immutable ./game_test_argomes game_is_immutable)
add_test(test_argomes_test_game_is_empty ./game_test_argomes game_is_empty)
add_test(test_argomes_test_game_equal ./game_test_argomes game_equal)
add_test(test_argomes_test_get_next_number ./game_test_argomes get_next_number)
add_test(test_argomes_test_get_number ./game_test_argomes get_number)
add_test(test_argomes_test_game_new ./game_test_argomes game_new)
add_test(test_argomes_test_game_get_square ./game_test_argomes game_get_square)





