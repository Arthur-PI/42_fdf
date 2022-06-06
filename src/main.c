/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/06 11:40:02 by apigeon          ###   ########.fr       */
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
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE);
	if (!mlx->win)
	{
		free_map(map);
		exit(error("Can't create an mlx window", 1));
	}
}

static void	usage(char *name)
{
	ft_printf("Usage: %s [file.fdf]\n", name);
	exit(1);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_img	img;
	t_map	*map;

	if (ac != 2)
		usage(av[0]);
	map = parse_file(av[1]);
	if (!map)
		exit(error("Error: an error occured while parsing the map", 1));
	init_mlx(&mlx, &map);
	setup_hooks(&mlx);
	img.img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_line(&img, (t_point){0, 0}, (t_point){WINDOW_WIDTH, WINDOW_HEIGHT}, RED);
	draw_line(&img, (t_point){0, WINDOW_HEIGHT}, (t_point){WINDOW_WIDTH, 0}, RED);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, img.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_display(mlx.mlx);
	free_map(&map);
	return (0);
}
