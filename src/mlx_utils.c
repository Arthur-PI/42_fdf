/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:14:40 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:38:33 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx(t_mlx *mlx)
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

t_img	get_image(t_mlx *mlx)
{
	t_img	img;

	img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.offset = mlx->map->offset;
	return (img);
}

void	free_map(t_map **map)
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
