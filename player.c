/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:07:14 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:09:24 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_player(t_all *all)
{
	if (all->plr->dir == 'W')
	{
		all->plr->dirx = (float)-1.0;
		all->plr->diry = (float)0.0;
	}
	else if (all->plr->dir == 'N')
	{
		all->plr->dirx = (float)0.0;
		all->plr->diry = (float)-1.0;
	}
	else if (all->plr->dir == 'E')
	{
		all->plr->dirx = (float)1.0;
		all->plr->diry = (float)0.0;
	}
	else if (all->plr->dir == 'S')
	{
		all->plr->dirx = (float)0.0;
		all->plr->diry = (float)1.0;
	}
	all->plr->planex = all->plr->diry * (float)(-0.66);
	all->plr->planey = all->plr->dirx * (float)0.66;
}

void	ft_parse_sprites(t_all *all, int n)
{
	int			x;
	int			y;
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite) * n);
	all->sprite = sprite;
	y = -1;
	while (all->map[++y])
	{
		x = -1;
		while (all->map[y][++x])
		{
			if (all->map[y][x] == '2')
			{
				n--;
				sprite[n].x = x + 0.5;
				sprite[n].y = y + 0.5;
			}
		}
	}
}

void	ft_parse_map(t_all *all)
{
	int	x;
	int	y;
	int	n;

	all->plr = (t_plr *)malloc(sizeof(t_plr));
	y = -1;
	n = 0;
	while (all->map[++y])
	{
		x = -1;
		while (all->map[y][++x])
		{
			if (ft_strchr("NEWS", all->map[y][x]))
			{
				all->plr->posx = (float)x + 0.5;
				all->plr->posy = (float)y + 0.5;
				all->plr->dir = all->map[y][x];
				all->map[y][x] = '0';
			}
			else if (all->map[y][x] == '2')
				n++;
		}
	}
	all->conf->numsprites = n;
	ft_parse_sprites(all, n);
}

int		*ft_tex_to_array(t_data *img, int width, int height)
{
	int		x;
	int		y;
	char	*dst;
	int		*texture;

	texture = (int *)malloc(sizeof(int) * width * height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			dst = img->addr + (y * img->line_length +
					x * (img->bits_per_pixel / 8));
			texture[width * y + x] = *(int *)dst;
			y++;
		}
		x++;
	}
	return (texture);
}

void	ft_make_textures(t_all *all)
{
	t_tex	*tex;
	t_data	img;
	int		w;
	int		h;

	tex = (t_tex *)malloc(sizeof(t_tex) * 5);
	all->tex = tex;
	all->vars->mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->ntext, &w, &h);
	all->tex[0].texture = ft_tex_to_array(&img, w, h);
	ft_set_wyh(all, w, h, 0);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->stext, &w, &h);
	all->tex[1].texture = ft_tex_to_array(&img, w, h);
	ft_set_wyh(all, w, h, 1);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->wtext, &w, &h);
	all->tex[2].texture = ft_tex_to_array(&img, w, h);
	ft_set_wyh(all, w, h, 2);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->etext, &w, &h);
	all->tex[3].texture = ft_tex_to_array(&img, w, h);
	ft_set_wyh(all, w, h, 3);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->sprite, &w, &h);
	all->tex[4].texture = ft_tex_to_array(&img, w, h);
	ft_set_wyh(all, w, h, 4);
	mlx_destroy_image(all->vars->mlx, img.img);
}
