/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:16:24 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	quit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_map(&mlx->map);
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
