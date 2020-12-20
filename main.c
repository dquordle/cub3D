#include <stdio.h>
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"

void ft_parser(char *file)
{
	int fd;
	t_list *head;
	char *line;

	line = NULL;
	head = NULL;
	fd = open (file, O_RDONLY);

}

int main(int argc, char **argv)
{
	void    *mlx;
	void    *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	printf("Hello, World!\n");

	ft_parser(argv[1]);
	return 0;
}
