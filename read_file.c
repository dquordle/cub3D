//
// Created by Dewayne Quordlepleen on 12/31/20.
//
//
//#include <stdio.h>
//#include "mlx.h"
//#include "cub3D.h"
//
//int main()
//{
//	int width;
//	int height;
//	void    *mlx;
//	t_data  img;
//	void 	*win;
//	int **texture;
//	char    *dst;
//
//
//
//	mlx = mlx_init();
//	img.img = mlx_xpm_file_to_image(mlx, "redbrick.xpm", &width, &height);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//							  &img.endian);
//	int north[width * height];
//	int x;
//	int y = 0;
//	printf("%d, %d\n", width, height);
//	while (y < height)
//	{
//		x = 0;
//		while (x < width)
//		{
//			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
//			north[width * y + x] = *(int*)dst;
//			x++;
//		}
//		y++;
//	}
//	texture[0] = north;
//	img.img = mlx_xpm_file_to_image(mlx, "wood.xpm", &width, &height);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//								 &img.endian);
//	int south[width * height];
//	printf("%d, %d\n", width, height);
//	y = 0;
//	while (y < height)
//	{
//		x = 0;
//		while (x < width)
//		{
//			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
//			south[width * y + x] = *(int*)dst;
//			x++;
//		}
//		y++;
//	}
//	texture[1] = south;
//	win = mlx_new_window(mlx, width, height, "keks");
//	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
//	mlx_loop(mlx);
//}
