/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 10:43:10 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	stop_loop(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

static void	handle_zoom_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_PLUS)
		zoom_map(mlx->map, 1 + ZOOM_SPEED);
	else if (keycode == KEY_MINUS)
		zoom_map(mlx->map, 1 - ZOOM_SPEED);
}

static void handle_translation_keys(int keycode, t_mlx *mlx)
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

static void	handle_rotation_keys(int keycode, t_mlx *mlx)
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

static int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		stop_loop(mlx);
	handle_zoom_keys(keycode, mlx);
	handle_translation_keys(keycode, mlx);
	handle_rotation_keys(keycode, mlx);
	render(mlx);
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, MASK_NO_EVENT, stop_loop, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, MASK_KEY_PRESS, key_hook, mlx);
}
