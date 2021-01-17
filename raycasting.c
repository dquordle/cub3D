/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:57:40 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 17:00:11 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_line_draw(t_draw *draw, t_all *all, int x)
{
	int y;

	draw->texx = (int)(draw->wallx * (double)all->tex[draw->texnum].width);
	if (draw->side == 0 && draw->raydirx > 0)
		draw->texx = all->tex[draw->texnum].width - draw->texx - 1;
	if (draw->side == 1 && draw->raydiry < 0)
		draw->texx = all->tex[draw->texnum].width - draw->texx - 1;
	y = draw->drawstart;
	while (y < draw->drawend)
	{
		draw->texy = (int)draw->texpos;
		draw->texpos += draw->step;
		my_mlx_pixel_put(all->vars->img, x, y++,
				all->tex[draw->texnum].texture[all->tex[draw->texnum].
				height * draw->texy + draw->texx]);
	}
	y = all->conf->height - 1;
	while (y > draw->drawend)
		my_mlx_pixel_put(all->vars->img, x, y--, all->conf->floor);
	y = 0;
	while (y < draw->drawstart)
		my_mlx_pixel_put(all->vars->img, x, y++, all->conf->ceiling);
}

void	ft_tex_conf(t_draw *draw, t_all *all)
{
	draw->lineheight = (int)(all->conf->height / draw->perpwalldist);
	draw->drawstart = -draw->lineheight / 2 + all->conf->height / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->lineheight / 2 + all->conf->height / 2;
	if (draw->drawend >= all->conf->height)
		draw->drawend = all->conf->height - 1;
	draw->texnum = 3;
	if (all->map[draw->mapy][draw->mapx] == '1')
	{
		if (draw->side == 1 && draw->stepy == 1)
			draw->texnum = 0;
		else if (draw->side == 1 && draw->stepy == -1)
			draw->texnum = 1;
		else if (draw->side == 0 && draw->stepx == 1)
			draw->texnum = 2;
	}
	if (draw->side == 0)
		draw->wallx = all->plr->posy + draw->perpwalldist * draw->raydiry;
	else
		draw->wallx = all->plr->posx + draw->perpwalldist * draw->raydirx;
	draw->wallx -= floor((draw->wallx));
	draw->step = 1.0 * all->tex[draw->texnum].height / draw->lineheight;
	draw->texpos = (draw->drawstart - all->conf->height / 2 +
			draw->lineheight / 2) * draw->step;
}

void	ft_cast_ray(t_draw *draw, t_all *all)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		draw->side = draw->sidedistx > draw->sidedisty;
		if (draw->sidedistx < draw->sidedisty)
		{
			draw->sidedistx += draw->deltadistx;
			draw->mapx += draw->stepx;
		}
		else
		{
			draw->sidedisty += draw->deltadisty;
			draw->mapy += draw->stepy;
		}
		if (all->map[draw->mapy][draw->mapx] == '1')
			hit = 1;
	}
	if (draw->side == 0)
		draw->perpwalldist = ((double)draw->mapx - all->plr->posx +
				(1 - draw->stepx) / 2) / draw->raydirx;
	else
		draw->perpwalldist = ((double)draw->mapy - all->plr->posy +
				(1 - draw->stepy) / 2) / draw->raydiry;
}

void	ft_setup(t_all *all, t_draw *draw, int x)
{
	draw->camerax = 2 * x / (double)all->conf->width - 1;
	draw->raydirx = all->plr->dirx + all->plr->planex * draw->camerax;
	draw->raydiry = all->plr->diry + all->plr->planey * draw->camerax;
	draw->mapx = (int)all->plr->posx;
	draw->mapy = (int)all->plr->posy;
	draw->deltadistx = fabs(1 / draw->raydirx);
	draw->deltadisty = fabs(1 / draw->raydiry);
	if (draw->raydirx < 0)
		draw->sidedistx = (all->plr->posx - draw->mapx) * draw->deltadistx;
	else
		draw->sidedistx = (draw->mapx + 1.0 - all->plr->posx) *
			draw->deltadistx;
	if (draw->raydiry < 0)
		draw->sidedisty = (all->plr->posy - draw->mapy) * draw->deltadisty;
	else
		draw->sidedisty = (draw->mapy + 1.0 - all->plr->posy) *
			draw->deltadisty;
	draw->stepx = draw->raydirx / fabs(draw->raydirx);
	draw->stepy = draw->raydiry / fabs(draw->raydiry);
}

void	ft_draw(t_all *all)
{
	t_draw	*draw;
	int		x;

	draw = (t_draw *)malloc(sizeof(t_draw));
	all->draw = draw;
	draw->distbuff = (double *)malloc(sizeof(double) * all->conf->width);
	x = 0;
	while (x < all->conf->width)
	{
		ft_setup(all, draw, x);
		ft_cast_ray(draw, all);
		ft_tex_conf(draw, all);
		ft_line_draw(draw, all, x);
		draw->distbuff[x++] = draw->perpwalldist;
	}
	ft_draw_sprites(all, draw);
	free(all->draw->distbuff);
	free(all->draw);
	free(all->drspr->dist);
	free(all->drspr->order);
	free(all->drspr);
}
