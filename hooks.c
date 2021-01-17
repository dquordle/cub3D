/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:43:55 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:49:54 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook3(int keycode, t_all *all, double movesp)
{
	if (keycode == 0)
	{
		if (all->map[(int)(all->plr->posy)][(int)(all->plr->posx -
					all->plr->planex * movesp)] != '1')
			all->plr->posx -= all->plr->planex * movesp;
		if (all->map[(int)(all->plr->posy - all->plr->planey * movesp)]
				[(int)(all->plr->posx)] != '1')
			all->plr->posy -= all->plr->planey * movesp;
	}
	else if (keycode == 2)
	{
		if (all->map[(int)(all->plr->posy)]
				[(int)(all->plr->posx + all->plr->planex * movesp)] != '1')
			all->plr->posx += all->plr->planex * movesp;
		if (all->map[(int)(all->plr->posy + all->plr->planey * movesp)]
				[(int)(all->plr->posx)] != '1')
			all->plr->posy += all->plr->planey * movesp;
	}
	else if (keycode == 53)
		ft_exit(all);
	ft_draw(all);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
							all->vars->img->img, 0, 0);
}

void	ft_hook2(int keycode, t_all *all, double movesp, double rotsp)
{
	double	tmd;
	double	tmp;

	tmd = all->plr->dirx;
	tmp = all->plr->planex;
	if (keycode == 123)
	{
		all->plr->dirx = all->plr->dirx * cos(-rotsp) -
			all->plr->diry * sin(-rotsp);
		all->plr->diry = tmd * sin(-rotsp) + all->plr->diry * cos(-rotsp);
		all->plr->planex = all->plr->planex * cos(-rotsp) -
			all->plr->planey * sin(-rotsp);
		all->plr->planey = tmp * sin(-rotsp) + all->plr->planey * cos(-rotsp);
	}
	else if (keycode == 124)
	{
		all->plr->dirx = all->plr->dirx * cos(rotsp) -
			all->plr->diry * sin(rotsp);
		all->plr->diry = tmd * sin(rotsp) + all->plr->diry * cos(rotsp);
		all->plr->planex = all->plr->planex * cos(rotsp) -
			all->plr->planey * sin(rotsp);
		all->plr->planey = tmp * sin(rotsp) + all->plr->planey * cos(rotsp);
	}
	ft_hook3(keycode, all, movesp);
}

void	hook(int keycode, t_all *all)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 0.15;
	rotspeed = 0.1;
	if (keycode == 126 || keycode == 13)
	{
		if (all->map[(int)(all->plr->posy)][(int)(all->plr->posx +
					all->plr->dirx * movespeed)] != '1')
			all->plr->posx += all->plr->dirx * movespeed;
		if (all->map[(int)(all->plr->posy + all->plr->diry * movespeed)]
			[(int)(all->plr->posx)] != '1')
			all->plr->posy += all->plr->diry * movespeed;
	}
	else if (keycode == 125 || keycode == 1)
	{
		if (all->map[(int)(all->plr->posy)][(int)(all->plr->posx -
					all->plr->dirx * movespeed)] != '1')
			all->plr->posx -= all->plr->dirx * movespeed;
		if (all->map[(int)(all->plr->posy - all->plr->diry * movespeed)]
				[(int)(all->plr->posx)] != '1')
			all->plr->posy -= all->plr->diry * movespeed;
	}
	ft_hook2(keycode, all, movespeed, rotspeed);
}

void	ft_set_wyh(t_all *all, int width, int height, int num)
{
	all->tex[num].width = width;
	all->tex[num].height = height;
}
