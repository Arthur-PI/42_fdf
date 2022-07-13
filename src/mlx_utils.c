/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:14:40 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 21:07:13 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->img = NULL;
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

t_img	*get_image(t_mlx *mlx)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	free_image(t_mlx *mlx, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(mlx->mlx, img->img);
		free(img);
	}
}

void	free_map(t_map **map)
{
	free_map_points((*map)->map, (*map)->y_len);
	free_map_points((*map)->map_copy, (*map)->y_len);
	free(*map);
}
