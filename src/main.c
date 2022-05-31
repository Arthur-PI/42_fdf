/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:12:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/05/31 12:31:36 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit(error("Can't initialize the mlx instance", 1));
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!mlx->win)
		exit(error("Can't create a new mlx window", 1));
}
*/

static void	usage(char *name)
{
	ft_printf("Usage: %s [file.fdf]\n", name);
	exit(1);
}

int	main(int ac, char **av)
{
	//t_mlx	mlx;
	int	*map;

	if (ac != 2)
		usage(av[0]);
	map = parse_file(av[1]);
	//init_mlx(&mlx);
	//setup_hooks(&mlx);
	//mlx_loop(mlx.mlx);
	return (0);
}
