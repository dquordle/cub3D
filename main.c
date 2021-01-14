#include "cub3D.h"

#define SCALE 50

void	ft_check_fyc(char *line)
{
	int i;

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
}

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
	int fd;

	i = 2;
	while (line[i] == ' ')
		i++;
	if ((fd = open(line + i, O_RDONLY)) == -1)
		ft_error(6);
	close(fd);
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
	else
		ft_error(3);
}

void	ft_conf(char *line, t_conf *conf)
{
	if (*line == 'R')
	{
		line++;
		while (*line == ' ')
			line++;
		conf->width = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		while (*line == ' ')
			line++;
		conf->height = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		if (conf->height <= 0 || conf->width <= 0 || *line)
			ft_error(4);
	}
	else if (*line == 'F' || *line == 'C')
	{
		ft_check_fyc(line);
		ft_floor_ceil(line, conf);
	}
	else
		ft_walls(line, conf);
}

void	ft_cut_conf(t_list **head, t_all *all)
{
	t_list *tmp;
	char *line;
	int i;

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
				break;
			else if (line[i])
				ft_error(3);
		}
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp);
	}
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
	int i;
	int j;
	int flag;

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
	ft_check_map(map);
	all->map = map;
}

void	ft_parser(char *file, t_all *all)
{
	int fd;
	t_list *head;
	t_list *tmp;
	char *line;
	t_conf *conf;

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_set_player(t_all *all)
{
	if (all->plr->dir == 'W')
	{
		all->plr->dirX = (float)-1.0;
		all->plr->dirY = (float)0.0;
	}
	else if (all->plr->dir == 'N')
	{
		all->plr->dirX = (float)0.0;
		all->plr->dirY = (float)-1.0;
	}
	else if (all->plr->dir == 'E')
	{
		all->plr->dirX = (float)1.0;
		all->plr->dirY = (float)0.0;
	}
	else if (all->plr->dir == 'S')
	{
		all->plr->dirX = (float)0.0;
		all->plr->dirY = (float)1.0;
	}
	all->plr->planeX = all->plr->dirY * (float)(-0.66);
	all->plr->planeY = all->plr->dirX * (float)0.66;
}

void	ft_parse_sprites(t_all *all, int n)
{
	int x;
	int y;
	t_sprite *sprite;

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
	int x;
	int y;
	int n;

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
				all->plr->posX = (float)x + 0.5;
				all->plr->posY = (float)y + 0.5;
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

int		*ft_texture_to_array(t_data *img, int width, int height)
{
	int x;
	int y;
	char    *dst;
	int		*texture;

	texture = (int *)malloc(sizeof(int) * width * height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								 &img->endian);
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
			texture[width * y + x] = *(int *) dst;
			y++;
		}
		x++;
	}
	return (texture);
}

void	ft_make_textures(t_all *all)
{
	int		**textures;
	t_data  img;
	int width;
	int height;

	textures = (int **)malloc(sizeof(int *) * 5);
	all->vars->mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->ntext, &width, &height);
	textures[0] = ft_texture_to_array(&img, width, height);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->stext, &width, &height);
	textures[1] = ft_texture_to_array(&img, width, height);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->wtext, &width, &height);
	textures[2] = ft_texture_to_array(&img, width, height);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->etext, &width, &height);
	textures[3] = ft_texture_to_array(&img, width, height);
	img.img = mlx_xpm_file_to_image(all->vars->mlx, all->conf->sprite, &width, &height);
	textures[4] = ft_texture_to_array(&img, width, height);
	mlx_destroy_image(all->vars->mlx, img.img);
	all->texture = textures;
}

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

//void	draw_picture(char **map, t_vars vars, t_plr *player)      2D MAP ? :/
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
