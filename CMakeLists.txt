cmake_minimum_required(VERSION 3.17)
project(Life C)

set(CMAKE_C_STANDARD 11)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(Life src/main/life_main.c src/main/life_util.h src/main/life_util.c)

target_link_libraries(Life ncurses)