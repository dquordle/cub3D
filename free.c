/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:37:16 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:37:22 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_all *all)
{
	int	i;

	if (all->argc == 2)
		mlx_destroy_window(all->vars->mlx, all->vars->win);
	i = 0;
	while (all->map[i])
		free(all->map[i++]);
	free(all->map);
	free(all->conf->ntext);
	free(all->conf->stext);
	free(all->conf->wtext);
	free(all->conf->etext);
	free(all->conf->sprite);
	free(all->conf);
	free(all->plr);
	free(all->sprite);
	i = 0;
	while (i < 5)
		free(all->tex[i++].texture);
	free(all->tex);
	mlx_destroy_image(all->vars->mlx, all->vars->img->img);
	free(all->vars->img);
	exit(0);
}
