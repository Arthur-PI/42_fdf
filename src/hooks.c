/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 19:04:23 by apigeon          ###   ########.fr       */
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
		foreach_point(mlx->map, 1 + ZOOM_SPEED, &zoom);
	else if (keycode == KEY_MINUS)
		foreach_point(mlx->map, 1 - ZOOM_SPEED, &zoom);
}

static void handle_translation_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W || keycode == KEY_ARROW_UP)
		foreach_point(mlx->map, -TRANSLATION_SPEED, &translate_y);
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
		foreach_point(mlx->map, TRANSLATION_SPEED, &translate_y);
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
		foreach_point(mlx->map, -TRANSLATION_SPEED, &translate_x);
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
		foreach_point(mlx->map, TRANSLATION_SPEED, &translate_x);
}

static void	handle_rotation_keys(int keycode, t_mlx *mlx)
{
	double speed;

	speed = ROTATION_SPEED;
	if (keycode == KEY_O)
		foreach_point(mlx->map, speed, &rotate_x);
	else if (keycode == KEY_P)
		foreach_point(mlx->map, -speed, &rotate_x);
	else if (keycode == KEY_L)
		foreach_point(mlx->map, speed, &rotate_y);
	else if (keycode == KEY_K)
		foreach_point(mlx->map, -speed, &rotate_y);
	else if (keycode == KEY_M)
		foreach_point(mlx->map, speed, &rotate_z);
	else if (keycode == KEY_N)
		foreach_point(mlx->map, -speed, &rotate_z);
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
