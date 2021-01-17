cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)

#include_directories(.)

add_executable(cub3D
        cub3D.h
        get_next_line.c
        libft.h
        main.c
        mlx.h
        raycasting.c
        read_file.c
        screenshot.c
        errors.c
        free.c
        draw_sprite.c
        hooks.c
        parser.c
        player.c
        )
target_link_libraries(cub3D /Users/dquordle/CLionProjects/cub3D/libft.a)
target_link_libraries(cub3D /Users/dquordle/CLionProjects/cub3D/cmake-build-debug/libmlx.dylib)
target_link_libraries(cub3D "-framework OpenGL")
target_link_libraries(cub3D "-framework AppKit")