/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:34:32 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 22:16:41 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_PLUS)
		zoom_map(mlx->map, 1 + ZOOM_SPEED);
	else if (keycode == KEY_MINUS)
		zoom_map(mlx->map, 1 - ZOOM_SPEED);
}

void	handle_translation_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		translate_map(mlx->map, 0, TRANSLATION_SPEED);
	else if (keycode == KEY_S)
		translate_map(mlx->map, 0, -TRANSLATION_SPEED);
	else if (keycode == KEY_A)
		translate_map(mlx->map, TRANSLATION_SPEED, 0);
	else if (keycode == KEY_D)
		translate_map(mlx->map, -TRANSLATION_SPEED, 0);
}

void	handle_rotation_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_O || keycode == KEY_ARROW_UP)
		rotate_map(mlx->map, ROTATION_SPEED, X_AXIS);
	else if (keycode == KEY_P || keycode == KEY_ARROW_DOWN)
		rotate_map(mlx->map, -ROTATION_SPEED, X_AXIS);
	else if (keycode == KEY_L || keycode == KEY_ARROW_RIGHT)
		rotate_map(mlx->map, ROTATION_SPEED, Y_AXIS);
	else if (keycode == KEY_K || keycode == KEY_ARROW_LEFT)
		rotate_map(mlx->map, -ROTATION_SPEED, Y_AXIS);
	else if (keycode == KEY_M)
		rotate_map(mlx->map, ROTATION_SPEED, Z_AXIS);
	else if (keycode == KEY_N)
		rotate_map(mlx->map, -ROTATION_SPEED, Z_AXIS);
}

void	handle_view_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_1)
		iso_view(mlx->map);
	else if (keycode == KEY_2)
		para_view(mlx->map);
}
