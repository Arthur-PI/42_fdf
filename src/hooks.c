/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 21:11:33 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	stop_loop(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

static int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		stop_loop(mlx);
	else
	{
		handle_zoom_keys(keycode, mlx);
		handle_translation_keys(keycode, mlx);
		handle_rotation_keys(keycode, mlx);
		handle_view_keys(keycode, mlx);
		if (render(mlx) == ERROR)
			stop_loop(mlx);
	}
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP)
		zoom_map(mlx->map, 1 + ZOOM_SPEED);
	else if (button == MOUSE_SCROLL_DOWN)
		zoom_map(mlx->map, 1 - ZOOM_SPEED);
	if (render(mlx) == ERROR)
		stop_loop(mlx);
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, MASK_NO_EVENT, stop_loop, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, MASK_KEY_PRESS, &key_hook, mlx);
	mlx_mouse_hook(mlx->win, &mouse_hook, mlx);
}
