cmake_minimum_required(VERSION 3.9)
project(ft_select)

set(CMAKE_CXX_STANDARD 11)

include_directories(libft/includes includes) # header directories
link_directories(libft) # library directories

add_executable(ft_select
        src/main.c src/main.c includes/ft_select.h src/terminal_mode.c src/list_functions.c src/execution.c libft/src/ft_strends.c src/moves.c src/helpers.c src/term_print.c src/signals.c libft/src/ft_lst_pushback.c)

target_link_libraries(ft_select -lft -ltermcap)
