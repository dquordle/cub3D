//
// Created by Dewayne Quordlepleen on 1/9/21.
//

#include "cub3D.h"

void 	ft_screenshot(t_all all)
{
	int fd;

	fd = open("first_image.bmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
	write(fd, "BM", 2);
	unsigned int size = 54 + screenWidth * screenHeight * 4; // size of file
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	unsigned int offbits = 54; // place of pixels
	write(fd, &offbits, 4);
	size = 40; // size of this structure
	write(fd, &size, 4);
	int width = screenWidth;
	int height = -1 * screenHeight;
	write(fd, &width, 4);
	write(fd, &height, 4);
	unsigned int planes = 1;
	write(fd, &planes, 2);
	unsigned int bitcount = 32;
	write(fd, &bitcount, 2);
	write(fd, "\0\0\0\0", 4); // bicompression
	write(fd, "\0\0\0\0", 4); // bisizeimage
	int bippm = 2835;
	write(fd, &bippm, 4);
	write(fd, &bippm, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	int y = 0;
	int x ;
	char *color;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			color = all.vars->img->addr + (y * all.vars->img->line_length + x * (all.vars->img->bits_per_pixel / 8));
			write(fd, &(*(int*)color), 4);
			x++;
		}
		y++;
	}
	close(fd);
}