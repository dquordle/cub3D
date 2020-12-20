cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(cub3D main.c start.c get_next_line.c)

target_link_libraries(cub3D /Users/dquordle/CLionProjects/cub3d/libmlx.a)
target_link_libraries(cub3D /Users/dquordle/CLionProjects/cub3d/libft.a)
target_link_libraries(cub3D "-framework OpenGL")
target_link_libraries(cub3D "-framework AppKit")