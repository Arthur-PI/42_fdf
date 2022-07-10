/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/28 14:47:57 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_map(t_map **map)
{
	int	y;

	y = 0;
	while (y < (*map)->y_len)
	{
		free((*map)->map[y]);
		y++;
	}
	free((*map)->map);
	free(*map);
}

static void	init_mlx(t_mlx *mlx, t_map **map)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		free_map(map);
		exit(error("Can't initialize the mlx instance", 1));
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx->win)
	{
		free_map(map);
		exit(error("Can't create an mlx window", 1));
	}
	if (WIN_WIDTH / (*map)->x_len > WIN_HEIGHT / (*map)->y_len)
		(*map)->offset = WIN_HEIGHT / (*map)->y_len;
	else
		(*map)->offset = WIN_WIDTH / (*map)->x_len;
}

static void	usage(char *name)
{
	ft_printf("Usage: %s [file.fdf]\n", name);
	exit(1);
}

/*
static void	test_lines(t_img *img)
{
	int		i;
	t_point	a;
	t_point	b;

	a.x = 500;
	a.y = 350;
	a.color = RED;
	b.color = RED;
	i = 0;
	while (i <= WIN_WIDTH)
	{
		b.x = i;
		b.y = 0;
		draw_line(img, a, b);
		b.y = WIN_HEIGHT;
		draw_line(img, a, b);
		i += 5;
	}
	i = 0;
	while (i <= WIN_HEIGHT)
	{
		b.x = 0;
		b.y = i;
		draw_line(img, a, b);
		b.x = WIN_WIDTH;
		draw_line(img, a, b);
		i += 5;
	}
}
*/

static void	print_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			printf("%3d", map->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

static void	draw_map(t_img *img, t_map *map)
{
	int	x;
	int	y;
	int	z;

	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			z = map->map[y][x];
			if (x != map->x_len - 1)
				draw_line(img, (t_point){x, y, z, RED}, (t_point){x + 1, y, z, RED});
			if (y != map->y_len - 1)
				draw_line(img, (t_point){x, y, z, RED}, (t_point){x, y + 1, z, RED});
			x++;
		}
		y++;
	}
}

// The mlx, the window and the image malloc 232 times
int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_img	img;
	t_map	*map;

	if (ac != 2)
		usage(av[0]);
	map = parse_file(av[1]);
	print_map(map);
	if (!map)
		exit(error("Error: an error occured while parsing the map", 1));
	init_mlx(&mlx, &map);
	setup_hooks(&mlx);
	img.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.offset = map->offset;
	//test_lines(&img);
	draw_map(&img, map);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, img.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
	free_map(&map);
	return (0);
}
