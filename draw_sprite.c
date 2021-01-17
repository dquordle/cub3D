/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:51:04 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:55:54 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_spr(t_all *all, t_drsp *spr, t_draw *draw)
{
	int	x;
	int	y;
	int	texx;
	int	texy;
	int	d;

	x = spr->drawstartx;
	while (x < spr->drawendx)
	{
		texx = (int)(256 * (x - (-spr->spritewidth / 2 + spr->sprscreenx)) *
				all->tex[4].width / spr->spritewidth) / 256;
		if (spr->transformy > 0 && spr->transformy < draw->distbuff[x])
		{
			y = spr->drawstarty - 1;
			while (++y < spr->drawendy)
			{
				d = y * 256 - all->conf->height * 128 + spr->sprheight * 128;
				texy = ((d * all->tex[4].height) / spr->sprheight) / 256;
				if (all->tex[4].texture[all->tex[4].height * texy + texx] != 0)
					my_mlx_pixel_put(all->vars->img, x, y, all->tex[4].
							texture[all->tex[4].height * texy + texx]);
			}
		}
		x++;
	}
}

void	ft_sprite_setup(t_all *all, t_drsp *spr, t_draw *draw)
{
	spr->transformx = spr->invdet * (all->plr->diry * spr->spritex -
			all->plr->dirx * spr->spritey);
	spr->transformy = spr->invdet * (-all->plr->planey * spr->spritex +
			all->plr->planex * spr->spritey);
	spr->sprscreenx = (int)((all->conf->width / 2) *
			(1 + spr->transformx / spr->transformy));
	spr->sprheight = abs((int)(all->conf->height / (spr->transformy)));
	spr->drawstarty = -spr->sprheight / 2 + all->conf->height / 2;
	if (spr->drawstarty < 0)
		spr->drawstarty = 0;
	spr->drawendy = spr->sprheight / 2 + all->conf->height / 2;
	if (spr->drawendy >= all->conf->height)
		spr->drawendy = all->conf->height - 1;
	spr->spritewidth = abs((int)(all->conf->height / (spr->transformy)));
	spr->drawstartx = -spr->spritewidth / 2 + spr->sprscreenx;
	if (spr->drawstartx < 0)
		spr->drawstartx = 0;
	spr->drawendx = spr->spritewidth / 2 + spr->sprscreenx;
	if (spr->drawendx >= all->conf->width)
		spr->drawendx = all->conf->width - 1;
	ft_draw_spr(all, spr, draw);
}

void	ft_draw_sprites(t_all *all, t_draw *draw)
{
	int		i;
	t_drsp	*spr;

	spr = (t_drsp *)malloc(sizeof(t_drsp));
	all->drspr = spr;
	spr->order = (int *)malloc(sizeof(int) * all->conf->numsprites);
	spr->dist = (double *)malloc(sizeof(double) * all->conf->numsprites);
	i = -1;
	while (++i < all->conf->numsprites)
	{
		spr->order[i] = i;
		spr->dist[i] = ((all->plr->posx - all->sprite[i].x) * (all->plr->posx -
					all->sprite[i].x) + (all->plr->posy - all->sprite[i].y) *
				(all->plr->posy - all->sprite[i].y));
	}
	sort_sprites(spr->order, spr->dist, all->conf->numsprites);
	i = -1;
	while (++i < all->conf->numsprites)
	{
		spr->spritex = all->sprite[spr->order[i]].x - all->plr->posx;
		spr->spritey = all->sprite[spr->order[i]].y - all->plr->posy;
		spr->invdet = 1.0 / (all->plr->planex * all->plr->diry -
				all->plr->dirx * all->plr->planey);
		ft_sprite_setup(all, spr, draw);
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	int		temp;
	double	dist_temp;

	while (amount > 1)
	{
		i = 0;
		while (i < amount - 1)
		{
			if (dist[i] < dist[i + 1])
			{
				temp = order[i];
				order[i] = order[i + 1];
				order[i + 1] = temp;
				dist_temp = dist[i];
				dist[i] = dist[i + 1];
				dist[i + 1] = dist_temp;
			}
			i++;
		}
		amount--;
	}
}
