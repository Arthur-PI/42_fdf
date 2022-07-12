/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:12:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:38:04 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_view(t_map *map)
{
	translate_map(map, -(WIN_WIDTH / 2), -(WIN_HEIGHT / 2));
	rotate_map(map, M_PI / 6, X_AXIS);
	rotate_map(map, -M_PI / 6, Y_AXIS);
	rotate_map(map, M_PI / 10, Z_AXIS);
	zoom_map(map, 0.7);
}

void	draw_map(t_mlx *mlx)
{
	int			x;
	int			y;
	t_point		**map;

	y = 0;
	map = mlx->map->map;
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

void	render(t_mlx *mlx)
{
	ft_bzero(mlx->img->addr, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}
