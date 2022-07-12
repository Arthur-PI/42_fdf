/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:34:32 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:40:11 by apigeon          ###   ########.fr       */
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
	if (keycode == KEY_W || keycode == KEY_ARROW_UP)
		translate_map(mlx->map, 0, TRANSLATION_SPEED);
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
		translate_map(mlx->map, 0, -TRANSLATION_SPEED);
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
		translate_map(mlx->map, TRANSLATION_SPEED, 0);
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
		translate_map(mlx->map, -TRANSLATION_SPEED, 0);
}

void	handle_rotation_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_O)
		rotate_map(mlx->map, ROTATION_SPEED, X_AXIS);
	else if (keycode == KEY_P)
		rotate_map(mlx->map, -ROTATION_SPEED, X_AXIS);
	else if (keycode == KEY_L)
		rotate_map(mlx->map, ROTATION_SPEED, Y_AXIS);
	else if (keycode == KEY_K)
		rotate_map(mlx->map, -ROTATION_SPEED, Y_AXIS);
	else if (keycode == KEY_M)
		rotate_map(mlx->map, ROTATION_SPEED, Z_AXIS);
	else if (keycode == KEY_N)
		rotate_map(mlx->map, -ROTATION_SPEED, Z_AXIS);
}
