cmake_minimum_required(VERSION 2.6)
project (takuzu-11c C)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
link_directories(${CMAKE_SOURCE_DIR})
add_executable(game_text game_text.c)
target_link_libraries(game_text m game)

