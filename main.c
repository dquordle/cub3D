#include <stdio.h>
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"
#include "cub3D.h"

#define SCALE 50

void	ft_floor_ceil(char *line, t_conf *conf)
{
	int color;
	int flag;

	flag = 0;
	if (line[0] == 'F')
		flag = 1;
	line++;
	while (*line == ' ')
		line++;
	color = ft_atoi(line) * 256 * 256;
	while (ft_isdigit(*line))
		line++;
	while (*line == ' ' || *line == ',')
		line++;
	color += ft_atoi(line) * 256;
	while (ft_isdigit(*line))
		line++;
	while (*line == ' ' || *line == ',')
		line++;
	color += ft_atoi(line);
	if (flag)
		conf->floor = color;
	else
		conf->ceiling = color;
}

void	ft_walls(char *line, t_conf *conf)
{
	int i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (line[0] == 'N' && line[1] == 'O')
		conf->ntext = line + i;
	else if (line[0] == 'S' && line[1] == 'O')
		conf->stext = line + i;
	else if (line[0] == 'W' && line[1] == 'E')
		conf->wtext = line + i;
	else if (line[0] == 'E' && line[1] == 'A')
		conf->etext = line + i;
	else if (line[0] == 'S' && line[1] == ' ')
		conf->sprite = line + i;
}

void	ft_conf(char *line, t_conf *conf)
{
	if (*line == 'R')
	{
		while (!ft_isdigit(*line))
			line++;
		conf->width = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		while (*line == ',' || *line == ' ')
			line++;
		conf->height = ft_atoi(line);
	}
	else if (*line == 'F' || *line == 'C')
		ft_floor_ceil(line, conf);
	else
		ft_walls(line, conf);
}

void ft_cut_conf(t_list **head, t_all *all)
{
	t_list *tmp;
	char *line;
	int i;
	t_conf *conf;

	conf = malloc(sizeof(t_conf));
	all->conf = conf;
	while (*head)
	{
		line = (char *)((*head)->content);
		if (ft_isalpha(line[0]))
			ft_conf(line, conf);
		else
		{
			i = 0;
			while (line[i] == ' ' || line[i] == '1')
				i++;
			if (!line[i] && i)
				break;
		}
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp);
	}
}

//void ft_cut_conf(t_list **head)
//{
//	char	**map;
//	int 	i;
//	char	*tmp;
//	int 	flag;
//	//do something with configurations, probably put em in some struct, idk
//	flag = 1;
//	while (flag)
//	{
//		i = 0;
//		tmp = (char *)((*head)->content);
//		while (tmp[i] == ' ' || ft_isdigit(tmp[i]))
//			i++;
//		if (!tmp[i] && i)
//			flag = 0;
//		else
//			*head = (*head)->next;
//	}
//}

void	ft_make_map(t_list **head, t_all *all)
{
	char **map;
	int i;
	t_list *tmp;

	map = ft_calloc(ft_lstsize(*head) + 1, sizeof(char *));
	i = 0;
	while (*head)
	{
		map[i++] = (*head)->content;
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	all->map = map;
}

void	ft_parser(char *file, t_all *all)
{
	int fd;
	t_list *head;
	t_list *tmp;
	char *line;

	line = NULL;
	head = NULL;
	fd = open(file, O_RDONLY); // check
	while (get_next_line(fd, &line))
	{
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
	}
	tmp = ft_lstnew(line);
	ft_lstadd_back(&head, tmp);
	//check for validacity
	ft_cut_conf(&head, all);
	ft_make_map(&head, all);
	close(fd);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


//int main(int argc, char **argv)
//{
//
//}

//void big_pixel_put(t_data *data, int x, int y, int color)
//{
//	int sx;
//	int sy;
//
//	sx = x * SCALE;
//	while (sx < (x + 1) * SCALE)
//	{
//		sy = y * SCALE;
//		while (sy < (y + 1) * SCALE)
//			my_mlx_pixel_put(data, sx, sy++, color);
//		sx++;
//	}
//}

//void player_put(t_data *data, float x, float y, int color)
//{
//	float sx;
//	float sy;
//
//	sx = x * SCALE;
//	while (sx < (x + 1) * SCALE)
//	{
//		sy = y * SCALE;
//		while (sy < (y + 1) * SCALE)
//			my_mlx_pixel_put(data, sx, sy++, color);
//		sx++;
//	}
//}

//void	draw_picture(char **map, t_vars vars, t_plr *player)
//{
//	t_data  img;
//	int x;
//	int y;
//
//	img.img = mlx_new_image(vars.mlx, 1920, 1080);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//								 &img.endian);
//	y = 0;
//	while (map[y])
//	{
//		x = 0;
//		while (map[y][x])
//		{
//			if (map[y][x] == '1')
//				big_pixel_put(&img, x, y, 0x00FFFFFF);
//			else if (map[y][x] == '0' || ft_strchr("NEWS", map[y][x]))
//				big_pixel_put(&img, x, y, 0x0000FF00);
//			else if (map[y][x] == '2')
//				big_pixel_put(&img, x, y, 0x00FF0000);
//			x++;
//		}
//		y++;
//	}
//	player_put(&img, player->x, player->y, 0x000000FF);
//	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
//}

//int 	hooker(int keycode, t_all *all)
//{
//	if (keycode == 124)
//		all->plr->x += 1.0/SCALE;
//	else if (keycode == 123)
//		all->plr->x -= 1.0/SCALE;
//	else if (keycode == 126)
//		all->plr->y -= 1.0/SCALE;
//	else if (keycode == 125)
//		all->plr->y += 1.0/SCALE;
//	draw_picture(all->map, *(all->vars), all->plr);
//	return (0);
//}

//int close_win(int keycode, t_vars *vars)
//{
//	if (keycode == 53)
//		mlx_destroy_window(vars->mlx, vars->win);
//}


//int main(int argc, char **argv)
//{
////	void    *mlx;
////	void    *mlx_win;
//	t_data  img;
//	int x;
//	int y;
//	char 	**map;
//	t_plr	player;
//	t_vars	vars;
//	t_all 	all;
//
//
//	vars.mlx = mlx_init();
//	img.img = mlx_new_image(vars.mlx, 1920, 1080);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//								 &img.endian);
//	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "keks");
//	map = ft_parser(argv[1]);
//	all.vars = &vars;
//	all.plr = &player;
//	all.map = map;
//	y = 0;
//	while (map[y])
//	{
//		x = 0;
//		while (map[y][x])
//		{
//			if (map[y][x] == '1')
//				big_pixel_put(&img, x, y, 0x00FFFFFF);
//			else if (map[y][x] == '0')
//				big_pixel_put(&img, x, y, 0x0000FF00);
//			else if (map[y][x] == '2')
//				big_pixel_put(&img, x, y, 0x00FF0000);
//			else if (ft_strchr("NEWS", map[y][x]))
//			{
//				big_pixel_put(&img, x, y, 0x000000FF);
//				player.x = x;
//				player.y = y;
//				//player.dir
//			}
//			x++;
//		}
//		y++;
//	}
//	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
////	mlx_key_hook(vars.win, hooker, &all);
//	mlx_hook(vars.win, 2, 1L<<0, hooker, &all);
//	mlx_loop(vars.mlx);
//	return 0;
//}
