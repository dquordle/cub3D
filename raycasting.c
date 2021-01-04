#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "cub3D.h"

//#define screenWidth 640
//#define screenHeight 480
//#define texWidth 64
//#define texHeight 64
#define mapWidth 24
#define mapHeight 24

//int worldMap[mapWidth][mapHeight]=
//		{
//				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
//				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
//				{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//				{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//				{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
//				{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
//				{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
//				{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//				{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
//				{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
//				{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
//				{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
//				{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//				{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
//				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//				{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
//				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//				{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
//				{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//				{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
//				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
//		};

//int buffer[screenHeight][screenWidth];

int 	hooker(int keycode, t_all *all)
{
//	if (keycode == 124)
//		all->plr->x += 1.0/SCALE;
//	else if (keycode == 123)
//		all->plr->x -= 1.0/SCALE;
//	else if (keycode == 126)
//		all->plr->y -= 1.0/SCALE;
//	else if (keycode == 125)
//		all->plr->y += 1.0/SCALE;
	double moveSpeed = 0.03 * 5.0; //the constant value is in squares/second
	double rotSpeed = 0.03 * 3.0; //the constant value is in radians/second

	//move forward if no wall in front of you
	if(keycode == 126)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX + all->plr->dirX * moveSpeed)] != '1')
			all->plr->posX += all->plr->dirX * moveSpeed;
		if (all->map[(int)(all->plr->posY + all->plr->dirY * moveSpeed)][(int)(all->plr->posX)] != '1')
			all->plr->posY += all->plr->dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if(keycode == 125)
	{
		if (all->map[(int)(all->plr->posY)][(int)(all->plr->posX - all->plr->dirX * moveSpeed)] != '1')
			all->plr->posX -= all->plr->dirX * moveSpeed;
		if(all->map[(int)(all->plr->posY - all->plr->dirY * moveSpeed)][(int)(all->plr->posX)] != '1')
			all->plr->posY -= all->plr->dirY * moveSpeed;
	}
	//rotate to the right
	if(keycode == 123)
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
	if(keycode == 124)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = all->plr->dirX;
		all->plr->dirX = all->plr->dirX * cos(rotSpeed) - all->plr->dirY * sin(rotSpeed);
		all->plr->dirY = oldDirX * sin(rotSpeed) + all->plr->dirY * cos(rotSpeed);
		double oldPlaneX = all->plr->planeX;
		all->plr->planeX = all->plr->planeX * cos(rotSpeed) - all->plr->planeY * sin(rotSpeed);
		all->plr->planeY = oldPlaneX * sin(rotSpeed) + all->plr->planeY * cos(rotSpeed);
	}
	ft_draw(*all, all->texture);
	if(keycode == 53)
	{
		mlx_destroy_window(all->vars->mlx, all->vars->win);
		exit(0);
	}
	//mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->vars-img.img, 0, 0);
	return (0);
}

int main()
{
	t_data img;
	char **map;
	t_plr player;
	t_vars vars;
	t_all all;
	int x;
	int y;
	struct Sprite sprite[numSprites];


	vars.mlx = mlx_init();
	img.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "keks");
	map = ft_parser("map.cub");
	all.vars = &vars;
	all.plr = &player;
	all.map = map;
	y = 0;
	int n = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NEWS", map[y][x]))
			{
				player.posX = x + 0.5;
				player.posY = y + 0.5;
				player.dir = map[y][x];
				map[y][x] = '0';
			}
			else if (map[y][x] == '2')
			{
				sprite[n].x = x + 0.5;
				sprite[n].y = y + 0.5;
				n++;
			}
			x++;
		}
		y++;
	}

	double posX = all.plr->posX, posY = all.plr->posY;  //x and y start position

	double dirX, dirY; //initial direction vector ????
	double planeX, planeY; //the 2d raycaster version of camera plane ?????
	if (all.plr->dir == 'W')
	{
		dirX = -1.0;
		dirY = 0.0;
		planeX = 0.0;
		planeY = -0.66;
	}
	else if (all.plr->dir == 'N')
	{
		dirX = 0.0;
		dirY = -1.0;
		planeX = 1.0;
		planeY = 0.0;
	}
	else if (all.plr->dir == 'E')
	{
		dirX = 1.0;
		dirY = 0.0;
		planeX = 0.0;
		planeY = 1.0;
	}
	else if (all.plr->dir == 'S')
	{
		dirX = 0.0;
		dirY = 1.0;
		planeX = -0.66;
		planeY = 0.0;
	}
	all.plr->dirX = dirX;
	all.plr->dirY = dirY;
	all.plr->planeX = planeX;
	all.plr->planeY = planeY;
	//generate some textures
//#if 0
	int texture[9][texHeight * texWidth];
	for (x = 0; x < texWidth; x++)
	{
		for (y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^(y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x !=
																	texWidth -
																	y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor +
										   65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] =
					256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor +
										   65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] =
					65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] =
					128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
	int width;
	int height;
	t_data  imgg;
	char    *dst;

	imgg.img = mlx_xpm_file_to_image(vars.mlx, "xpms/colorstone.xpm", &width, &height);
	imgg.addr = mlx_get_data_addr(imgg.img, &imgg.bits_per_pixel, &imgg.line_length,
								 &imgg.endian);
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			dst = imgg.addr + (y * imgg.line_length + x * (imgg.bits_per_pixel / 8));
			texture[0][width * y + x] = *(int*)dst;
			y++;
		}
		x++;
	}
	imgg.img = mlx_xpm_file_to_image(vars.mlx, "xpms/barrel.xpm", &width, &height);
	imgg.addr = mlx_get_data_addr(imgg.img, &imgg.bits_per_pixel, &imgg.line_length,
								  &imgg.endian);
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			dst = imgg.addr + (y * imgg.line_length + x * (imgg.bits_per_pixel / 8));
			texture[8][width * y + x] = *(int*)dst;
			y++;
		}
		x++;
	}
//	int *lol;
//	lol = mlx_xpm_file_to_image(vars.mlx, "xpms/eagle.xpm", &width, &height);
//	x = 0;
//	while (x < width)
//	{
//		y = 0;
//		while (y < height)
//		{
//			texture[2][width * x + y] = lol[width * y + x];
//			y++;
//		}
//		x++;
//	}

//#else
//	//generate some textures
//	unsigned long tw, th;
//	loadImage(texture[0], tw, th, "pics/eagle.png");
//	loadImage(texture[1], tw, th, "pics/redbrick.png");
//	loadImage(texture[2], tw, th, "pics/purplestone.png");
//	loadImage(texture[3], tw, th, "pics/greystone.png");
//	loadImage(texture[4], tw, th, "pics/bluestone.png");
//	loadImage(texture[5], tw, th, "pics/mossy.png");
//	loadImage(texture[6], tw, th, "pics/wood.png");
//	loadImage(texture[7], tw, th, "pics/colorstone.png");
//#endif

	//start the main loop
	all.texture = texture;
	all.sprite = sprite;
	ft_draw(all, texture);
	mlx_hook(all.vars->win, 2, 1L<<0, hooker, &all);
	mlx_loop(all.vars->mlx);
}

void	ft_draw(t_all all, int texture[9][texHeight * texWidth])
{
	double posX = all.plr->posX, posY = all.plr->posY;  //x and y start position
	double dirX, dirY; //initial direction vector ????
	double planeX, planeY; //the 2d raycaster version of camera plane ?????
	int x, y;
	char **map;
	t_data img;
	double ZBuffer[screenWidth];
	int spriteOrder[numSprites];
	double spriteDistance[numSprites];

	img.img = mlx_new_image(all.vars->mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	dirX = all.plr->dirX;
	dirY = all.plr->dirY;
	planeX = all.plr->planeX;
	planeY = all.plr->planeY;
	map = all.map;

	for(x = 0; x < screenWidth; x++)
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
		spriteDistance[i] = ((posX - all.sprite[i].x) * (posX - all.sprite[i].x) + (posY - all.sprite[i].y) * (posY - all.sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);

	//after sorting the sprites, do the projection and draw them
	for (int i = 0; i < numSprites; i++)
	{
	//translate sprite position to relative to camera
		double spriteX = all.sprite[spriteOrder[i]].x - posX;
		double spriteY = all.sprite[spriteOrder[i]].y - posY;

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
					int color = texture[8][texHeight * texY + texX]; //get current color from the texture
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

	mlx_put_image_to_window(all.vars->mlx, all.vars->win, img.img, 0, 0);

	//speed modifiers
}

void 	sortSprites(int* order, double* dist, int amount)
{
	int i;
	int temp;

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
			}
			i++;
		}
		amount--;
	}
}
