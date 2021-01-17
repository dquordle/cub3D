/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:37:40 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:38:18 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lets_play(t_all *all)
{
	t_data	*img;
	int		width;
	int		height;

	mlx_get_screen_size(all->vars->mlx, &width, &height);
	if (width < all->conf->width)
		all->conf->width = width;
	if (height < all->conf->height)
		all->conf->height = height;
	img = (t_data *)malloc(sizeof(t_data));
	all->vars->img = img;
	img->img = mlx_new_image(all->vars->mlx, all->conf->width,
			all->conf->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_draw(all);
	all->vars->win = mlx_new_window(all->vars->mlx, all->conf->width,
			all->conf->height, "cubik");
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
			all->vars->img->img, 0, 0);
}

int		main(int argc, char **argv)
{
	t_vars	vars;
	t_all	all;

	if (argc < 2 || argc > 3 || (argc == 3 && ft_strncmp(argv[2], "--save", 7)))
		ft_error(8);
	all.vars = &vars;
	all.argc = argc;
	ft_parser(argv[1], &all);
	ft_parse_map(&all);
	ft_set_player(&all);
	ft_make_textures(&all);
	if (argc == 3)
		ft_screenshot(&all);
	else
	{
		ft_lets_play(&all);
		mlx_hook(all.vars->win, 2, 1L << 0, hook, &all);
		mlx_hook(all.vars->win, 17, 0, ft_exit, &all);
		mlx_loop(all.vars->mlx);
	}
}
