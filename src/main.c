/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/10 16:03:00 by apigeon          ###   ########.fr       */
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
	mlx->map->zoom = 1;
	mlx->map->trans.tx = 0;
	mlx->map->trans.ty = 0;
	if (WIN_WIDTH / mlx->map->x_len > WIN_HEIGHT / mlx->map->y_len)
		mlx->map->offset = WIN_HEIGHT / mlx->map->y_len;
	else
		mlx->map->offset = WIN_WIDTH / mlx->map->x_len;
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
			printf("%3d", map->map[y][x].z);
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
	t_rotation	rot;

	y = 0;
	rot.rx = 0;
	rot.ry = M_PI_2;
	rot.rz = M_PI_4;
	while (y < mlx->map->y_len)
	{
		x = 0;
		while (x < mlx->map->x_len)
		{
			if (x != mlx->map->x_len - 1)
				draw_line(mlx->img, mlx->map->map[y][x], mlx->map->map[y][x + 1], rot, mlx->map->trans, mlx->map->zoom);
			if (y != mlx->map->y_len - 1)
				draw_line(mlx->img, mlx->map->map[y][x], mlx->map->map[y + 1][x], rot, mlx->map->trans, mlx->map->zoom);
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
	print_map(mlx.map);
	init_mlx(&mlx);
	img = get_image(&mlx);
	mlx.img = &img;
	draw_map(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
	setup_hooks(&mlx);
	mlx_loop(mlx.mlx);
	quit(&mlx);
	return (0);
}
