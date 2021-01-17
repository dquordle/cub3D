/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:00:25 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 17:00:48 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_walls(char *line, t_conf *conf)
{
	int	i;
	int	fd;

	i = 2;
	while (line[i] == ' ')
		i++;
	if ((fd = open(line + i, O_RDONLY)) == -1)
		ft_error(6);
	close(fd);
	if (line[0] == 'N' && line[1] == 'O')
		conf->ntext = ft_strtrim(line + i, " ");
	else if (line[0] == 'S' && line[1] == 'O')
		conf->stext = ft_strtrim(line + i, " ");
	else if (line[0] == 'W' && line[1] == 'E')
		conf->wtext = ft_strtrim(line + i, " ");
	else if (line[0] == 'E' && line[1] == 'A')
		conf->etext = ft_strtrim(line + i, " ");
	else if (line[0] == 'S' && line[1] == ' ')
		conf->sprite = ft_strtrim(line + i, " ");
	else
		ft_error(3);
	free(line);
}

void	ft_check_spaces(char **map, int i, int j)
{
	if (i == 0 || j == 0)
		ft_error(7);
	if (!(map[i + 1]) || !(map[i][j + 1]))
		ft_error(7);
	if (ft_strlen(map[i - 1]) <= j || ft_strlen(map[i + 1]) <= j)
		ft_error(7);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		ft_error(7);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		ft_error(7);
}

void	ft_check_map(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = -1;
	while (map[i])
	{
		j = 0;
		if (!map[i][j])
			ft_error(7);
		while (map[i][j])
		{
			if (!(ft_strchr(" 012NEWS", map[i][j])))
				ft_error(7);
			if (ft_strchr("02NEWS", map[i][j]))
				ft_check_spaces(map, i, j);
			if (ft_strchr("NEWS", map[i][j]))
				flag++;
			j++;
		}
		i++;
	}
	if (flag)
		ft_error(7);
}

void	ft_make_map(t_list **head, t_all *all)
{
	char	**map;
	int		i;
	t_list	*tmp;

	map = ft_calloc(ft_lstsize(*head) + 1, sizeof(char *));
	i = 0;
	while (*head)
	{
		map[i++] = (*head)->content;
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	ft_check_map(map);
	all->map = map;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
