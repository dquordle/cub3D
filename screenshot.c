/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:56:22 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:57:20 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_picture(t_all *all, int fd)
{
	int		x;
	int		y;
	char	*color;

	y = 0;
	while (y < all->conf->height)
	{
		x = 0;
		while (x < all->conf->width)
		{
			color = all->vars->img->addr + (y * all->vars->img->line_length +
					x * (all->vars->img->bits_per_pixel / 8));
			write(fd, &(*(int*)color), 4);
			x++;
		}
		y++;
	}
}

void	ft_header(t_all *all, int fd)
{
	unsigned int	temp;
	int				x;

	write(fd, &all->conf->width, 4);
	x = -1 * all->conf->height;
	write(fd, &x, 4);
	temp = 1;
	write(fd, &temp, 2);
	temp = 32;
	write(fd, &temp, 2);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	x = 2835;
	write(fd, &x, 4);
	write(fd, &x, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	ft_picture(all, fd);
}

void	ft_screenshot(t_all *all)
{
	int				fd;
	t_data			*img;
	unsigned int	temp;

	img = (t_data *)malloc(sizeof(t_data));
	all->vars->img = img;
	img->img = mlx_new_image(all->vars->mlx, all->conf->width,
			all->conf->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_draw(all);
	fd = open("first_image.bmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
	write(fd, "BM", 2);
	temp = 54 + all->conf->width * all->conf->height * 4;
	write(fd, &temp, 4);
	write(fd, "\0\0\0\0", 4);
	temp = 54;
	write(fd, &temp, 4);
	temp = 40;
	write(fd, &temp, 4);
	ft_header(all, fd);
	close(fd);
	ft_exit(all);
}
