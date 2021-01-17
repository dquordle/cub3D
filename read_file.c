/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:16 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:50:43 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_floor_ceil(char *line, t_conf *conf)
{
	int	color;
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	color = ft_atoi(line + i) * 256 * 256;
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	color += ft_atoi(line + i) * 256;
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	color += ft_atoi(line + i);
	if (line[0] == 'F')
		conf->floor = color;
	else
		conf->ceiling = color;
	free(line);
}

void	ft_check_fyc(char *line, t_conf *conf)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	if (ft_atoi(line + i) < 0 || ft_atoi(line + i) > 255)
		ft_error(5);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	if (ft_atoi(line + i) < 0 || ft_atoi(line + i) > 255)
		ft_error(5);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	if (ft_atoi(line + i) < 0 || ft_atoi(line + i) > 255)
		ft_error(5);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i])
		ft_error(5);
	ft_floor_ceil(line, conf);
}

void	ft_conf(char *line, t_conf *conf)
{
	int	i;

	i = 1;
	if (*line == 'R')
	{
		while (line[i] == ' ')
			i++;
		conf->width = ft_atoi(line + i);
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ')
			i++;
		conf->height = ft_atoi(line + i);
		while (ft_isdigit(line[i]))
			i++;
		if (conf->height <= 0 || conf->width <= 0 || line[i])
			ft_error(4);
		free(line);
	}
	else if (*line == 'F' || *line == 'C')
		ft_check_fyc(line, conf);
	else
		ft_walls(line, conf);
}

void	ft_cut_conf(t_list **head, t_all *all)
{
	t_list	*tmp;
	char	*line;
	int		i;

	while (*head)
	{
		line = (char *)((*head)->content);
		if (ft_isalpha(line[0]))
			ft_conf(line, all->conf);
		else
		{
			i = 0;
			while (line[i] == ' ' || line[i] == '1')
				i++;
			if (!line[i] && i)
				break ;
			else if (line[i])
				ft_error(3);
			free(line);
		}
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp);
	}
}

void	ft_parser(char *file, t_all *all)
{
	int		fd;
	t_list	*head;
	t_list	*tmp;
	char	*line;
	t_conf	*conf;

	if (!(conf = malloc(sizeof(t_conf))))
		ft_error(1);
	all->conf = conf;
	line = NULL;
	head = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(2);
	while (get_next_line(fd, &line))
	{
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
	}
	tmp = ft_lstnew(line);
	ft_lstadd_back(&head, tmp);
	ft_cut_conf(&head, all);
	ft_make_map(&head, all);
	close(fd);
}
