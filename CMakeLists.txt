cmake_minimum_required(VERSION 3.9)
project(ft_select)

set(CMAKE_CXX_STANDARD 11)

include_directories(libft/includes includes) # header directories
link_directories(libft) # library directories

add_executable(minishell
        src/main.c src/main.c)

target_link_libraries(ft_select -lft)
