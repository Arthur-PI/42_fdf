/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:12:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 21:01:47 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	render(t_mlx *mlx)
{
	t_img	*old_img;
	t_img	*new_img;

	old_img = mlx->img;
	new_img = get_image(mlx);
	if (!new_img)
		return (error("can't create a new image during render", ERROR));
	mlx->img = new_img;
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, new_img->img, 0, 0);
	free_image(mlx, old_img);
	return (NO_ERROR);
}
