/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:37:02 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:37:07 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(int er_type)
{
	write(2, "Error\n", 6);
	if (er_type == 1)
		write(2, "Malloc error\n", 13);
	else if (er_type == 2)
		write(2, "Couldn't open map file\n", 23);
	else if (er_type == 3)
		write(2, "Invalid map file configuration\n", 31);
	else if (er_type == 4)
		write(2, "Invalid resolution\n", 19);
	else if (er_type == 5)
		write(2, "Invalid floor or ceiling color\n", 31);
	else if (er_type == 6)
		write(2, "Couldn't open texture file\n", 27);
	else if (er_type == 7)
		write(2, "Invalid map\n", 12);
	else if (er_type == 8)
		write(2, "Invalid arguments\n", 18);
	exit(0);
}
