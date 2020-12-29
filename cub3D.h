//
// Created by Dewayne Quordlepleen on 12/20/20.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H

#define screenWidth 1000
#define screenHeight 800
#define texWidth 64
#define texHeight 64

typedef struct  s_vars {
	void    *mlx;
	void    *win;
}               t_vars;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

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

typedef struct	s_all
{
	t_vars		*vars;
	t_plr		*plr;
	char		**map;
	int			done;
	int			**texture;
}				t_all;

int		get_next_line(int fd, char **line);
char	**ft_parser(char *file);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_draw(t_all all, int texture[8][texHeight * texWidth]);

#endif //CUB3D_CUB3D_H
