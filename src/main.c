/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 12:56:44 by apigeon          ###   ########.fr       */
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

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		free_map(&mlx->map);
		exit(error("Can't initialize the mlx instance", 1));
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx->win)
	{
		free_map(&mlx->map);
		exit(error("Can't create an mlx window", 1));
	}
}

static void	usage(char *name)
{
	ft_printf("Usage: %s [file.fdf]\n", name);
	exit(1);
}

void	print_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	printf("\nMap: \n");
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			//printf("(%.2f,%.2f,%.2f) ", map->map[y][x].x, map->map[y][x].y, map->map[y][x].z);
			printf("(%x) ", map->map[y][x].color);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	draw_map(t_mlx *mlx)
{
	int			x;
	int			y;
	t_point		**map;

	y = 0;
	map = mlx->map->map;
	//print_map(mlx->map);
	while (y < mlx->map->y_len)
	{
		x = 0;
		while (x < mlx->map->x_len)
		{
			if (x != mlx->map->x_len - 1)
				draw_line(mlx, map[y][x], map[y][x + 1]);
			if (y != mlx->map->y_len - 1)
				draw_line(mlx, map[y][x], map[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	quit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_map(&mlx->map);
}

t_img	get_image(t_mlx *mlx)
{
	t_img	img;

	img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.offset = mlx->map->offset;
	return (img);
}

void	iso_view(t_map *map)
{
	translate_map(map, -(WIN_WIDTH / 2), -(WIN_HEIGHT / 2));
	zoom_map(map, 0.7);
}

void	render(t_mlx *mlx)
{
	ft_bzero(mlx->img->addr, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

// The mlx, the window and the image malloc 232 times
int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_img	img;

	if (ac != 2)
		usage(av[0]);
	mlx.map = parse_file(av[1]);
	if (!mlx.map)
		exit(error("Error: an error occured while parsing the map", 1));
	init_mlx(&mlx);
	img = get_image(&mlx);
	mlx.img = &img;
	iso_view(mlx.map);
	render(&mlx);
	setup_hooks(&mlx);
	mlx_loop(mlx.mlx);
	quit(&mlx);
	return (0);
}
