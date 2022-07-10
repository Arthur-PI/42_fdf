/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/10 16:18:36 by apigeon          ###   ########.fr       */
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
	//printf("KEY: %d\n", keycode);
	if (keycode == KEY_ESC)
		stop_loop(mlx);
	else if (keycode == KEY_W || keycode == KEY_ARROW_UP)
		mlx->map->trans.ty -= TRANSLATE_SPEED;
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
		mlx->map->trans.ty += TRANSLATE_SPEED;
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
		mlx->map->trans.tx -= TRANSLATE_SPEED;
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
		mlx->map->trans.tx += TRANSLATE_SPEED;
	else if (keycode == KEY_PLUS)
		mlx->map->zoom *= 1 + ZOOM_SPEED;
	else if (keycode == KEY_MINUS)
		mlx->map->zoom *= 1 - ZOOM_SPEED;
	ft_bzero(mlx->img->addr, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, MASK_NO_EVENT, stop_loop, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, MASK_KEY_PRESS, key_hook, mlx);
}
