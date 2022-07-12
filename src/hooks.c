/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:42:08 by apigeon          ###   ########.fr       */
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
		render(mlx);
	}
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, MASK_NO_EVENT, stop_loop, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, MASK_KEY_PRESS, key_hook, mlx);
}
