//
// Created by Dewayne Quordlepleen on 12/20/20.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

#define screenWidth 1920
#define screenHeight 1080
#define texWidth 64
#define texHeight 64
#define numSprites 3

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct  s_vars {
	void    *mlx;
	void    *win;
	t_data	*img;
}               t_vars;


typedef struct	s_plr
{
	float		posX;
	float		posY;
	float		dirX;
	float		dirY;
	float 		planeX;
	float		planeY;
	char		dir;
}				  t_plr;

typedef struct	s_sprite
{
	double x;
	double y;
}				t_sprite;

typedef struct	s_conf
{
	int 		width;
	int 		height;
	char 		*ntext;
	char		*stext;
	char 		*etext;
	char		*wtext;
	char 		*sprite;
	int			floor;
	int 		ceiling;
	int			numsprites;
}				t_conf;

typedef struct 		s_tex
{
	int				*texture;
	int 			width;
	int				height;
}					t_tex;

typedef struct		s_all
{
	t_vars			*vars;
	t_plr			*plr;
	char			**map;
	int				**texture;
	t_tex			*tex;
	t_sprite		*sprite;
	t_conf			*conf;
}					t_all;



int		get_next_line(int fd, char **line);
void	ft_parser(char *file, t_all *all);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_draw(t_all *all);
void 	sortSprites(int* order, double* dist, int amount);
//void big_pixel_put(t_data *data, int x, int y, int color);
void 	ft_screenshot(t_all all);
void	ft_error(int er_type);
void	ft_parse_map(t_all *all);
void	ft_set_player(t_all *all);
void	ft_make_textures(t_all *all);

#endif //CUB3D_CUB3D_H
