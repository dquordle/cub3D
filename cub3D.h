/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:51:21 by dquordle          #+#    #+#             */
/*   Updated: 2021/01/17 16:43:22 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		*img;
}				t_vars;

typedef struct	s_plr
{
	float		posx;
	float		posy;
	float		dirx;
	float		diry;
	float		planex;
	float		planey;
	char		dir;
}				t_plr;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_conf
{
	int			width;
	int			height;
	char		*ntext;
	char		*stext;
	char		*etext;
	char		*wtext;
	char		*sprite;
	int			floor;
	int			ceiling;
	int			numsprites;
}				t_conf;

typedef struct	s_tex
{
	int			*texture;
	int			width;
	int			height;
}				t_tex;

typedef struct	s_draw
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			texnum;
	double		wallx;
	double		step;
	double		texpos;
	int			texx;
	int			texy;
	double		*distbuff;
}				t_draw;

typedef struct	s_drsp
{
	int			*order;
	double		*dist;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			sprscreenx;
	int			sprheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
}				t_drsp;

typedef struct	s_all
{
	t_vars		*vars;
	t_plr		*plr;
	char		**map;
	t_tex		*tex;
	t_sprite	*sprite;
	t_conf		*conf;
	t_draw		*draw;
	t_drsp		*drspr;
	int			argc;
}				t_all;

int				get_next_line(int fd, char **line);
void			ft_parser(char *file, t_all *all);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_draw(t_all *all);
void			sort_sprites(int *order, double *dist, int amount);
void			ft_screenshot(t_all *all);
void			ft_error(int er_type);
void			ft_parse_map(t_all *all);
void			ft_set_player(t_all *all);
void			ft_make_textures(t_all *all);
void			ft_exit(t_all *all);
void			hook(int keycode, t_all *all);
void			hook2(int keycode, t_all *all);
void			hook3(int keycode, t_all *all);
void			ft_draw_spr(t_all *all, t_drsp *spr, t_draw *draw);
void			ft_sprite_setup(t_all *all, t_drsp *spr, t_draw *draw);
void			ft_draw_sprites(t_all *all, t_draw *draw);
void			ft_lets_play(t_all *all);
void			ft_walls(char *line, t_conf *conf);
void			ft_check_spaces(char **map, int i, int j);
void			ft_check_map(char **map);
void			ft_make_map(t_list **head, t_all *all);
void			ft_set_player(t_all *all);
void			ft_parse_sprites(t_all *all, int n);
void			ft_parse_map(t_all *all);
int				*ft_tex_to_array(t_data *img, int width, int height);
void			ft_make_textures(t_all *all);
void			ft_line_draw(t_draw *draw, t_all *all, int x);
void			ft_tex_conf(t_draw *draw, t_all *all);
void			ft_cast_ray(t_draw *draw, t_all *all);
void			ft_setup(t_all *all, t_draw *draw, int x);
void			ft_floor_ceil(char *line, t_conf *conf);
void			ft_check_fyc(char *line, t_conf *conf);
void			ft_conf(char *line, t_conf *conf);
void			ft_cut_conf(t_list **head, t_all *all);
void			ft_header(t_all *all, int fd);
void			ft_picture(t_all *all, int fd);
void			ft_set_wyh(t_all *all, int width, int height, int num);

#endif
