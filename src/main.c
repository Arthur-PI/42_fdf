/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 20:07:45 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	quit(t_mlx *mlx)
{
	free_image(mlx, mlx->img);
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

	if (ac != 2)
		usage(av[0]);
	mlx.map = parse_file(av[1]);
	if (!mlx.map)
		exit(error("Error: an error occured while parsing the map", 1));
	init_mlx(&mlx);
	iso_view(mlx.map);
	setup_hooks(&mlx);
	if (render(&mlx) == NO_ERROR)
		mlx_loop(mlx.mlx);
	quit(&mlx);
	return (0);
}
