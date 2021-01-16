#include "cub3D.h"

void	ft_hooker3(int keycode, t_all *all, double movesp, double rotsp)
{
	if (keycode == 0)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX -
		all->plr->planeX * movesp)] != '1')
			all->plr->posX -= all->plr->planeX * movesp;
		if(all->map[(int)(all->plr->posY - all->plr->planeY * movesp)]
		[(int)(all->plr->posX)] != '1')
			all->plr->posY -= all->plr->planeY * movesp;
	}
	else if (keycode == 2)
	{
		if (all->map[(int)(all->plr->posY)]
		[(int)(all->plr->posX + all->plr->planeX * movesp)] != '1')
			all->plr->posX += all->plr->planeX * movesp;
		if(all->map[(int)(all->plr->posY + all->plr->planeY * movesp)]
		[(int)(all->plr->posX)] != '1')
			all->plr->posY += all->plr->planeY * movesp;
	}
	else if (keycode == 53)
	{
		mlx_destroy_window(all->vars->mlx, all->vars->win); //// TODO: Заменить на одну строку ft_exit();
		exit(0);
	}
	ft_draw(all);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
						 all->vars->img->img, 0, 0);
}

void	ft_hooker2(int keycode, t_all *all, double movesp, double rotsp)
{
	double tmd;
	double tmp;

	tmd = all->plr->dirX;
	tmp = all->plr->planeX;
	if (keycode == 123)
	{
		all->plr->dirX = all->plr->dirX * cos(-rotsp) -
				all->plr->dirY * sin(-rotsp);
		all->plr->dirY = tmd * sin(-rotsp) + all->plr->dirY * cos(-rotsp);
		all->plr->planeX = all->plr->planeX * cos(-rotsp) -
				all->plr->planeY * sin(-rotsp);
		all->plr->planeY = tmp * sin(-rotsp) + all->plr->planeY * cos(-rotsp);
	}
	else if (keycode == 124)
	{
		all->plr->dirX = all->plr->dirX * cos(rotsp) -
				all->plr->dirY * sin(rotsp);
		all->plr->dirY = tmd * sin(rotsp) + all->plr->dirY * cos(rotsp);
		all->plr->planeX = all->plr->planeX * cos(rotsp) -
				all->plr->planeY * sin(rotsp);
		all->plr->planeY = tmp * sin(rotsp) + all->plr->planeY * cos(rotsp);
	}
	ft_hooker3(keycode, all, movesp, rotsp);
}


void	hooker(int keycode, t_all *all)
{
	double moveSpeed;
	double rotSpeed;

	moveSpeed = 0.15;
	rotSpeed = 0.1;
	if (keycode == 126 || keycode == 13)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX +
		all->plr->dirX * moveSpeed)] != '1')
			all->plr->posX += all->plr->dirX * moveSpeed;
		if (all->map[(int)(all->plr->posY + all->plr->dirY * moveSpeed)]
		[(int)(all->plr->posX)] != '1')
			all->plr->posY += all->plr->dirY * moveSpeed;
	}
	else if (keycode == 125 || keycode == 1)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX -
		all->plr->dirX * moveSpeed)] != '1')
			all->plr->posX -= all->plr->dirX * moveSpeed;
		if(all->map[(int)(all->plr->posY - all->plr->dirY * moveSpeed)]
		[(int)(all->plr->posX)] != '1')
			all->plr->posY -= all->plr->dirY * moveSpeed;
	}
	ft_hooker2(keycode, all, moveSpeed, rotSpeed);
}

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
								   all->conf->height, "keks");
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
						 all->vars->img->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_vars vars;
	t_all all;

	int nprinted = printf("[%.d],[%.i],[%.u],[%.x],[%.X]", 0, 0, 0, 0, 0);
	printf("\t<- printf\t= %d\n", nprinted);
	if (argc < 2 || argc > 3 || (argc == 3 && ft_strncmp(argv[2], "--save", 7)))
		ft_error(8);
	printf("%d\n", 9 < 8);
	all.vars = &vars;
	ft_parser(argv[1], &all);
	ft_parse_map(&all);
	ft_set_player(&all);
	ft_make_textures(&all);
	if (argc == 3)
		ft_screenshot(all);
	else
	{
		ft_lets_play(&all);
		mlx_hook(all.vars->win, 2, 1L << 0, hooker, &all);
		mlx_loop(all.vars->mlx);
	}
}

void	ft_tex_conf(t_draw *draw, t_all *all)
{
	draw->lineHeight = (int)(all->conf->height / draw->perpWallDist);
	draw->drawStart = -draw->lineHeight / 2 + all->conf->height / 2;
	if (draw->drawStart < 0)
		draw->drawStart = 0;
	draw->drawEnd = draw->lineHeight / 2 + all->conf->height / 2;
	if (draw->drawEnd >= all->conf->height)
		draw->drawEnd = all->conf->height - 1;
	draw->texNum = 3;
	if (all->map[draw->mapY][draw->mapX] == '1')
	{
		if (draw->side == 1 && draw->stepY == 1)
			draw->texNum = 0;
		else if (draw->side == 1 && draw->stepY == -1)
			draw->texNum = 1;
		else if (draw->side == 0 && draw->stepX == 1)
			draw->texNum = 2;
	}
	if (draw->side == 0)
		draw->wallX = all->plr->posY + draw->perpWallDist * draw->rayDirY;
	else
		draw->wallX = all->plr->posX + draw->perpWallDist * draw->rayDirX;
	draw->wallX -= floor((draw->wallX));
	draw->step = 1.0 * all->tex[draw->texNum].height / draw->lineHeight;
	draw->texPos = (draw->drawStart - all->conf->height / 2 +
			draw->lineHeight / 2) * draw->step;
}

void	ft_cast_ray(t_draw *draw, t_all *all)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		draw->side = draw->sideDistX > draw->sideDistY;
		if (draw->sideDistX < draw->sideDistY)
		{
			draw->sideDistX += draw->deltaDistX;
			draw->mapX += draw->stepX;
		}
		else
		{
			draw->sideDistY += draw->deltaDistY;
			draw->mapY += draw->stepY;
		}
		if (all->map[draw->mapY][draw->mapX] == '1')
			hit = 1;
	}
	if (draw->side == 0)
		draw->perpWallDist = ((double)draw->mapX - all->plr->posX +
				(1 - draw->stepX) / 2) / draw->rayDirX;
	else
		draw->perpWallDist = ((double)draw->mapY - all->plr->posY +
				(1 - draw->stepY) / 2) / draw->rayDirY;
}

void	ft_setup(t_all *all, t_draw *draw, int x)
{
	draw->cameraX = 2 * x / (double)all->conf->width - 1;
	draw->rayDirX = all->plr->dirX + all->plr->planeX * draw->cameraX;
	draw->rayDirY = all->plr->dirY + all->plr->planeY * draw->cameraX;
	draw->mapX = (int)all->plr->posX;
	draw->mapY = (int)all->plr->posY;
	draw->deltaDistX = fabs(1 / draw->rayDirX);
	draw->deltaDistY = fabs(1 / draw->rayDirY);
	if (draw->rayDirX < 0)
		draw->sideDistX = (all->plr->posX - draw->mapX) * draw->deltaDistX;
	else
		draw->sideDistX = (draw->mapX + 1.0 - all->plr->posX) * draw->deltaDistX;
	if (draw->rayDirY < 0)
		draw->sideDistY = (all->plr->posY - draw->mapY) * draw->deltaDistY;
	else
		draw->sideDistY = (draw->mapY + 1.0 - all->plr->posY) * draw->deltaDistY;
	draw->stepX = draw->rayDirX / fabs(draw->rayDirX);
	draw->stepY = draw->rayDirY / fabs(draw->rayDirY);
}

void	ft_line_draw(t_draw *draw, t_all *all, int x)
{
	int y;

	draw->texX = (int)(draw->wallX * (double)all->tex[draw->texNum].width);
	if (draw->side == 0 && draw->rayDirX > 0)
		draw->texX = all->tex[draw->texNum].width - draw->texX - 1;
	if (draw->side == 1 && draw->rayDirY < 0)
		draw->texX = all->tex[draw->texNum].width - draw->texX - 1;
	y = draw->drawStart;
	while (y < draw->drawEnd)
	{
		draw->texY = (int)draw->texPos;
		draw->texPos += draw->step;
		my_mlx_pixel_put(all->vars->img, x, y++,
				   all->tex[draw->texNum].texture[all->tex[draw->texNum]
				   .height * draw->texY + draw->texX]);
	}
	y = all->conf->height - 1;
	while (y > draw->drawEnd)
		my_mlx_pixel_put(all->vars->img, x, y--, all->conf->floor);
	y = 0;
	while (y < draw->drawStart)
		my_mlx_pixel_put(all->vars->img, x, y++, all->conf->ceiling);
}

void	ft_draw_spr(t_all *all, t_drsp *spr, t_draw *draw)
{
	int x;
	int y;
	int texX;
	int texY;
	int d;

	x = spr->drawStartX;
	while (x < spr->drawEndX)
	{
		texX = (int)(256 * (x - (-spr->spriteWidth / 2 + spr->sprScreenX)) *
				all->tex[4].width / spr->spriteWidth) / 256;
		if (spr->transformY > 0 && spr->transformY < draw->distBuff[x])
		{
			y = spr->drawStartY - 1;
			while (++y < spr->drawEndY)
			{
				d = y * 256 - all->conf->height * 128 + spr->sprHeight * 128;
				texY = ((d * all->tex[4].height) / spr->sprHeight) / 256;
				if (all->tex[4].texture[all->tex[4].height * texY + texX] != 0)
					my_mlx_pixel_put(all->vars->img, x, y,all->tex[4].
					texture[all->tex[4].height * texY + texX]);
			}
		}
		x++;
	}
}

void	ft_sprite_setup(t_all *all, t_drsp *spr, t_draw *draw)
{
	spr->transformX = spr->invDet * (all->plr->dirY * spr->spriteX -
			all->plr->dirX * spr->spriteY);
	spr->transformY = spr->invDet * (-all->plr->planeY * spr->spriteX +
			all->plr->planeX * spr->spriteY);
	spr->sprScreenX = (int)((all->conf->width / 2) *
			(1 + spr->transformX / spr->transformY));
	spr->sprHeight = abs((int)(all->conf->height / (spr->transformY)));
	spr->drawStartY = -spr->sprHeight / 2 + all->conf->height / 2;
	if (spr->drawStartY < 0)
		spr->drawStartY = 0;
	spr->drawEndY = spr->sprHeight / 2 + all->conf->height / 2;
	if (spr->drawEndY >= all->conf->height)
		spr->drawEndY = all->conf->height - 1;
	spr->spriteWidth = abs((int)(all->conf->height / (spr->transformY)));
	spr->drawStartX = -spr->spriteWidth / 2 + spr->sprScreenX;
	if (spr->drawStartX < 0)
		spr->drawStartX = 0;
	spr->drawEndX = spr->spriteWidth / 2 + spr->sprScreenX;
	if (spr->drawEndX >= all->conf->width)
		spr->drawEndX = all->conf->width - 1;
	ft_draw_spr(all, spr, draw);
}

void	ft_draw_sprites(t_all *all, t_draw *draw)
{
	int i;
	t_drsp spr;

	spr.order = (int *) malloc(sizeof(int) * all->conf->numsprites);
	spr.dist = (double *) malloc(sizeof(double) * all->conf->numsprites);
	i = -1;
	while (++i < all->conf->numsprites)
	{
		spr.order[i] = i;
		spr.dist[i] = ((all->plr->posX - all->sprite[i].x) * (all->plr->posX -
				all->sprite[i].x) + (all->plr->posY - all->sprite[i].y) *
						(all->plr->posY - all->sprite[i].y));
	}
	sortSprites(spr.order, spr.dist, all->conf->numsprites);
	i = -1;
	while (++i < all->conf->numsprites)
	{
		spr.spriteX = all->sprite[spr.order[i]].x - all->plr->posX;
		spr.spriteY = all->sprite[spr.order[i]].y - all->plr->posY;
		spr.invDet = 1.0 / (all->plr->planeX * all->plr->dirY -
							all->plr->dirX * all->plr->planeY);
		ft_sprite_setup(all, &spr, draw);
	}
}




void	ft_draw(t_all *all)
{
	t_draw *draw;
	int		x;

	draw = (t_draw *)malloc(sizeof(t_draw));
	draw->distBuff = (double *)malloc(sizeof(double) * all->conf->width);
	x = 0;
	while (x < all->conf->width)
	{
		ft_setup(all, draw, x);
		ft_cast_ray(draw, all);
		ft_tex_conf(draw, all);
		ft_line_draw(draw, all, x);
		draw->distBuff[x++] = draw->perpWallDist;
	}
	ft_draw_sprites(all, draw);
}

//void	ft_draw(t_all *all)
//{
//	double posX, posY;  //x and y start position
//	double dirX, dirY; //initial direction vector ????
//	double planeX, planeY; //the 2d raycaster version of camera plane ?????
//	int x, y;
//	char **map;
//	t_data img;
//	double ZBuffer[screenWidth];
//	int spriteOrder[numSprites];
//	double spriteDistance[numSprites];
//
//	posX = all->plr->posX;
//	posY = all->plr->posY;
//	img = *all->vars->img;
//	dirX = all->plr->dirX;
//	dirY = all->plr->dirY;
//	planeX = all->plr->planeX;
//	planeY = all->plr->planeY;
//	map = all->map;
//
//	for (x = 0; x < screenWidth; x++)
//	{
//		//calculate ray position and direction
//		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
//		double rayDirX = dirX + planeX*cameraX;
//		double rayDirY = dirY + planeY*cameraX;
//
//		//which box of the map we're in
//		int mapX = (int)posX;
//		int mapY = (int)posY;
//
//		//length of ray from current position to next x or y-side
//		double sideDistX;
//		double sideDistY;
//
//		//length of ray from one x or y-side to next x or y-side
//		double deltaDistX = fabs(1 / rayDirX);
//		double deltaDistY = fabs(1 / rayDirY);
//		double perpWallDist;
//
//		//what direction to step in x or y-direction (either +1 or -1)
//		int stepX;
//		int stepY;
//
//		int hit = 0; //was there a wall hit?
//		int side; //was a NS or a EW wall hit?
//
//		//calculate step and initial sideDist
//		if(rayDirX < 0)
//		{
//			stepX = -1;
//			sideDistX = (posX - mapX) * deltaDistX;
//		}
//		else
//		{
//			stepX = 1;
//			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//		}
//		stepX = rayDirX / fabs(rayDirX);
//		if(rayDirY < 0)
//		{
//			stepY = -1;
//			sideDistY = (posY - mapY) * deltaDistY;
//		}
//		else
//		{
//			stepY = 1;
//			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//		}
//		//perform DDA
//		while (hit == 0)
//		{
//			//jump to next map square, OR in x-direction, OR in y-direction
//			if(sideDistX < sideDistY)
//			{
//				sideDistX += deltaDistX;
//				mapX += stepX;
//				side = 0;
//			}
//			else
//			{
//				sideDistY += deltaDistY;
//				mapY += stepY;
//				side = 1;
//			}
//			//Check if ray has hit a wall
//			if (map[mapY][mapX] == '1')
//				hit = 1;
//		}
//
//		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
//		if (side == 0)
//			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//		else
//			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
//
//		//Calculate height of line to draw on screen
//		int lineHeight = (int)(screenHeight / perpWallDist);
//
//		//calculate lowest and highest pixel to fill in current stripe
//		int drawStart = -lineHeight / 2 + screenHeight / 2;
//		if (drawStart < 0)
//			drawStart = 0;
//		int drawEnd = lineHeight / 2 + screenHeight / 2;
//		if (drawEnd >= screenHeight)
//			drawEnd = screenHeight - 1;
//
//		//texturing calculations
//		int texNum;
//		if (map[mapY][mapX] == '1') //1 subtracted from it so that texture 0 can be used!
//		{
//			if (side == 1 && stepY == 1) //North wall
//				texNum = 0;
//			else if (side == 1 && stepY == -1) //South wall
//				texNum = 1;
//			else if (side == 0 && stepX == 1)
//				texNum = 2;
//			else
//				texNum = 3;
//		}
//		else
//			texNum = 4;
//		//calculate value of wallX
//		double wallX; //where exactly the wall was hit
//		if (side == 0)
//			wallX = posY + perpWallDist * rayDirY;
//		else
//			wallX = posX + perpWallDist * rayDirX;
//		wallX -= floor((wallX));
//
//		//x coordinate on the texture
//		int texX = (int)(wallX * (double)texWidth);		//// THIS BLOCK ISNT IN ANY FUNCTION
//		if (side == 0 && rayDirX > 0)
//			texX = texWidth - texX - 1;
//		if (side == 1 && rayDirY < 0)
//			texX = texWidth - texX - 1;
//
//		// How much to increase the texture coordinate per screen pixel
//		double step = 1.0 * texHeight / lineHeight;
//		// Starting texture coordinate
//		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
//		for (y = drawStart; y < drawEnd; y++)
//		{
//			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//			int texY = (int)texPos; //& (texHeight - 1);
//			texPos += step;
//			int color = all->tex[texNum].texture[texHeight * texY + texX];
//			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//			if (side == 1)
//				color = (color >> 1) & 8355711;
//			//buffer[y][x] = color;
//			my_mlx_pixel_put(&img, x, y, color);
//		}
//		// Floor
//		for (y = screenHeight - 1; y > drawEnd; y--)
//		{
//			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
////			int texY = (int)texPos & (texHeight - 1);
////			texPos += step;
////			int color = texture[texNum][texHeight * texY + texX];
//			int color = 0xc0c8ff; //x00DC6400;
//			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
////			if (side == 1)
////				color = (color >> 1) & 8355711;
//			//buffer[y][x] = color;
//			my_mlx_pixel_put(&img, x, y, color);
//		}
//		// Ceiling
//		for(y = 0; y < drawStart; y++)
//		{
//			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
////			int texY = (int)texPos & (texHeight - 1);
////			texPos += step;
////			int color = texture[texNum][texHeight * texY + texX];
////			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
////			if (side == 1)
////				color = (color >> 1) & 8355711;
////			//buffer[y][x] = color;
//			int color = 0xffdab9;
//			my_mlx_pixel_put(&img, x, y, color);
//		}
//		//SET THE ZBUFFER FOR THE SPRITE CASTING
//		ZBuffer[x] = perpWallDist; //perpendicular distance is used
//	}
//
//
////SPRITE CASTING
////sort sprites from far to close
//	for (int i = 0; i < numSprites; i++)
//	{
//		spriteOrder[i] = i;
//		spriteDistance[i] = ((posX - all->sprite[i].x) * (posX - all->sprite[i].x) + (posY - all->sprite[i].y) * (posY - all->sprite[i].y)); //sqrt not taken, unneeded
//	}
//	sortSprites(spriteOrder, spriteDistance, numSprites);
//
//	//after sorting the sprites, do the projection and draw them
//	for (int i = 0; i < numSprites; i++)
//	{
//	//translate sprite position to relative to camera
//		double spriteX = all->sprite[spriteOrder[i]].x - posX;
//		double spriteY = all->sprite[spriteOrder[i]].y - posY;
//
//	//transform sprite with the inverse camera matrix
//	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
//	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
//	// [ planeY   dirY ]                                          [ -planeY  planeX ]
//
//		double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication
//
//		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
//		double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
//
//		int spriteScreenX = (int)((screenWidth / 2) * (1 + transformX / transformY));
//
//		//parameters for scaling and moving the sprites
//		#define uDiv 1
//		#define vDiv 1
//		#define vMove 0.0
//		int vMoveScreen = (int)(vMove / transformY);
//
//		//calculate height of the sprite on screen
//		int spriteHeight = abs((int)(screenHeight / (transformY)) / vDiv); //using "transformY" instead of the real distance prevents fisheye
//		//calculate lowest and highest pixel to fill in current stripe
//		int drawStartY = -spriteHeight / 2 + screenHeight / 2 + vMoveScreen;
//		if (drawStartY < 0)
//			drawStartY = 0;
//		int drawEndY = spriteHeight / 2 + screenHeight / 2 + vMoveScreen;
//		if (drawEndY >= screenHeight)
//			drawEndY = screenHeight - 1;
//
//		//calculate width of the sprite
//		int spriteWidth = abs((int)(screenHeight / (transformY))) / uDiv;
//		int drawStartX = -spriteWidth / 2 + spriteScreenX;
//		if (drawStartX < 0)
//			drawStartX = 0;
//		int drawEndX = spriteWidth / 2 + spriteScreenX;
//		if (drawEndX >= screenWidth)
//			drawEndX = screenWidth;
//
//		//loop through every vertical stripe of the sprite on screen
//		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//		{
//			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
//			//the conditions in the if are:
//			//1) it's in front of camera plane so you don't see things behind you
//			//2) it's on the screen (left)
//			//3) it's on the screen (right)
//			//4) ZBuffer, with perpendicular distance
//			if (transformY > 0 && transformY < ZBuffer[stripe])
//			{
//				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
//				{
//					int d = (y - vMoveScreen) * 256 - screenHeight * 128 + spriteHeight *
//																128; //256 and 128 factors to avoid floats
//					int texY = ((d * texHeight) / spriteHeight) / 256;
//					int color = all->tex[4].texture[texHeight * texY + texX]; //get current color from the texture
//					if ((color & 0x00FFFFFF) != 0)
//						my_mlx_pixel_put(&img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
//					//big_pixel_put(&img, 10, 10, 2134568);
//				}
//			}
//		}
//	}
//}

void 	sortSprites(int *order, double *dist, int amount)
{
	int i;
	int temp;
	double dist_temp;

	while (amount > 1)
	{
		i = 0;
		while (i < amount - 1)
		{
			if (dist[i] < dist[i + 1])
			{
				temp = order[i];
				order[i] = order[i + 1];
				order[i + 1] = temp;
				dist_temp = dist[i];
				dist[i] = dist[i + 1];
				dist[i + 1] = dist_temp;
			}
			i++;
		}
		amount--;
	}
}
