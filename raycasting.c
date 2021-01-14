#include "cub3D.h"

int 	hooker(int keycode, t_all *all)
{
	double moveSpeed = 0.03 * 5.0; //the constant value is in squares/second
	double rotSpeed = 0.03 * 3.0; //the constant value is in radians/second

	//move forward if no wall in front of you
	if (keycode == 126 || keycode == 13)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX + all->plr->dirX * moveSpeed)] != '1')
			all->plr->posX += all->plr->dirX * moveSpeed;
		if (all->map[(int)(all->plr->posY + all->plr->dirY * moveSpeed)][(int)(all->plr->posX)] != '1')
			all->plr->posY += all->plr->dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keycode == 125 || keycode == 1)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX - all->plr->dirX * moveSpeed)] != '1')
			all->plr->posX -= all->plr->dirX * moveSpeed;
		if(all->map[(int)(all->plr->posY - all->plr->dirY * moveSpeed)][(int)(all->plr->posX)] != '1')
			all->plr->posY -= all->plr->dirY * moveSpeed;
	}
	if (keycode == 0)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX - all->plr->planeX * moveSpeed)] != '1')
			all->plr->posX -= all->plr->planeX * moveSpeed;
		if(all->map[(int)(all->plr->posY - all->plr->planeY * moveSpeed)][(int)(all->plr->posX)] != '1')
			all->plr->posY -= all->plr->planeY * moveSpeed;
	}
	if (keycode == 2)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX + all->plr->planeX * moveSpeed)] != '1')
			all->plr->posX += all->plr->planeX * moveSpeed;
		if(all->map[(int)(all->plr->posY + all->plr->planeY * moveSpeed)][(int)(all->plr->posX)] != '1')
			all->plr->posY += all->plr->planeY * moveSpeed;
	}
	//rotate to the right
	if (keycode == 123)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = all->plr->dirX;
		all->plr->dirX = all->plr->dirX * cos(-rotSpeed) - all->plr->dirY * sin(-rotSpeed);
		all->plr->dirY = oldDirX * sin(-rotSpeed) + all->plr->dirY * cos(-rotSpeed);
		double oldPlaneX = all->plr->planeX;
		all->plr->planeX = all->plr->planeX * cos(-rotSpeed) - all->plr->planeY * sin(-rotSpeed);
		all->plr->planeY = oldPlaneX * sin(-rotSpeed) + all->plr->planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (keycode == 124)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = all->plr->dirX;
		all->plr->dirX = all->plr->dirX * cos(rotSpeed) - all->plr->dirY * sin(rotSpeed);
		all->plr->dirY = oldDirX * sin(rotSpeed) + all->plr->dirY * cos(rotSpeed);
		double oldPlaneX = all->plr->planeX;
		all->plr->planeX = all->plr->planeX * cos(rotSpeed) - all->plr->planeY * sin(rotSpeed);
		all->plr->planeY = oldPlaneX * sin(rotSpeed) + all->plr->planeY * cos(rotSpeed);
	}
	ft_draw(all, all->texture);
	if (keycode == 53)
	{
		mlx_destroy_window(all->vars->mlx, all->vars->win);
		exit(0);
	}
	//mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->vars-img.img, 0, 0);
	return (0);
}

//int main(int argc, char **argv)
//{
//	t_all all;
//	t_conf *conf;
//
//	if (argc < 2 || argc > 3)
//		ft_error(8);
//	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
//		ft_error(8);
//	if (!(conf = malloc(sizeof(t_conf))))
//		ft_error(1);
//	all.conf = conf;
//	ft_parser(argv[1], &all);
//	ft_draw();
//	if (argc == 2)
//	{
//		mlx_new_window();
//		put_image_to_win();
//		hook;
//		loop;
//	}
//	else
//		ft_screenshot();
//}

int main(int argc, char **argv)
{
	t_data img;
	t_vars vars;
	t_all all;

//	all = (t_all *)malloc(sizeof(t_all));
	all.vars = &vars;
	ft_parser(argv[1], &all);
	ft_parse_map(&all);
	ft_set_player(&all);
	ft_make_textures(&all);
//	all->vars->mlx = mlx_init();
	all.vars->win = mlx_new_window(all.vars->mlx, all.conf->width,
								   all.conf->height, "keks");
	all.vars->img = &img;
	img.img = mlx_new_image(all.vars->mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
//	mlx_get_screen_size(all.vars->mlx, &w, &h);
//	printf("%d, %d\n", w, h);
//	mlx_do_key_autorepeatoff(all.vars->mlx);
	ft_draw(&all, all.texture);
//	ft_screenshot(*all);
	mlx_hook(all.vars->win, 2, 1L<<0, hooker, &all);
	mlx_loop(all.vars->mlx);
}

void	ft_draw(t_all *all, int **texture)
{
	double posX, posY;  //x and y start position
	double dirX, dirY; //initial direction vector ????
	double planeX, planeY; //the 2d raycaster version of camera plane ?????
	int x, y;
	char **map;
	t_data img;
	double ZBuffer[screenWidth];
	int spriteOrder[numSprites];
	double spriteDistance[numSprites];

	posX = all->plr->posX;
	posY = all->plr->posY;
	img = *all->vars->img;
	dirX = all->plr->dirX;
	dirY = all->plr->dirY;
	planeX = all->plr->planeX;
	planeY = all->plr->planeY;
	map = all->map;

	for (x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX*cameraX;
		double rayDirY = dirY + planeY*cameraX;

		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (map[mapY][mapX] == '1')
				hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		//texturing calculations
		int texNum;
		if (map[mapY][mapX] == '1') //1 subtracted from it so that texture 0 can be used!
		{
			if (side == 1 && stepY == 1) //North wall
				texNum = 0;
			else if (side == 1 && stepY == -1) //South wall
				texNum = 1;
			else if (side == 0 && stepX == 1)
				texNum = 2;
			else
				texNum = 3;
		}
		else
			texNum = 4;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for (y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			//buffer[y][x] = color;
			my_mlx_pixel_put(&img, x, y, color);
		}
		// Floor
		for (y = screenHeight - 1; y > drawEnd; y--)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//			int texY = (int)texPos & (texHeight - 1);
//			texPos += step;
//			int color = texture[texNum][texHeight * texY + texX];
			int color = 0xc0c8ff; //x00DC6400;
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//			if (side == 1)
//				color = (color >> 1) & 8355711;
			//buffer[y][x] = color;
			my_mlx_pixel_put(&img, x, y, color);
		}
		// Ceiling
		for(y = 0; y < drawStart; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//			int texY = (int)texPos & (texHeight - 1);
//			texPos += step;
//			int color = texture[texNum][texHeight * texY + texX];
//			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//			if (side == 1)
//				color = (color >> 1) & 8355711;
//			//buffer[y][x] = color;
			int color = 0xffdab9;
			my_mlx_pixel_put(&img, x, y, color);
		}
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}


//SPRITE CASTING
//sort sprites from far to close
	for (int i = 0; i < numSprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((posX - all->sprite[i].x) * (posX - all->sprite[i].x) + (posY - all->sprite[i].y) * (posY - all->sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);

	//after sorting the sprites, do the projection and draw them
	for (int i = 0; i < numSprites; i++)
	{
	//translate sprite position to relative to camera
		double spriteX = all->sprite[spriteOrder[i]].x - posX;
		double spriteY = all->sprite[spriteOrder[i]].y - posY;

	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
		double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((screenWidth / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(screenHeight / (transformY)) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + screenHeight / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + screenHeight / 2 + vMoveScreen;
		if (drawEndY >= screenHeight)
			drawEndY = screenHeight - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(screenHeight / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= screenWidth)
			drawEndX = screenWidth - 1;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < screenWidth && transformY < ZBuffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y - vMoveScreen) * 256 - screenHeight * 128 + spriteHeight *
																128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					int color = texture[4][texHeight * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
					//big_pixel_put(&img, 10, 10, 2134568);
				}
			}
		}
	}


		//drawBuffer(buffer[0]);
//
//		for(int y = 0; y < h; y++)
//			for(int x = 0; x < w; x++)
//				buffer[y][x] = 0; //clear the buffer instead of cls()
		//timing for input and FPS counter
//		oldTime = time;
//		time = getTicks();
//		double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
//		print(1.0 / frameTime); //FPS counter
//		redraw();

	mlx_put_image_to_window(all->vars->mlx, all->vars->win, img.img, 0, 0);

	//speed modifiers
}

void 	sortSprites(int *order, double *dist, int amount)
{
	int i;
	int temp;
	double dtemp;

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
				dtemp = dist[i];
				dist[i] = dist[i + 1];
				dist[i + 1] = dtemp;
			}
			i++;
		}
		amount--;
	}
}
