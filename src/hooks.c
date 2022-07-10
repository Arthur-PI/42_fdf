/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/10 19:11:55 by apigeon          ###   ########.fr       */
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
		mlx->map->zoom *= 1 + ZOOM_SPEED;
	else if (keycode == KEY_MINUS)
		mlx->map->zoom *= 1 - ZOOM_SPEED;
}

static void handle_translation_keys(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W || keycode == KEY_ARROW_UP)
		mlx->map->trans.ty -= TRANSLATION_SPEED;
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
		mlx->map->trans.ty += TRANSLATION_SPEED;
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
		mlx->map->trans.tx -= TRANSLATION_SPEED;
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
		mlx->map->trans.tx += TRANSLATION_SPEED;
}

static void	round_rotation(t_rotation *rot)
{
	double twoPI = M_PI * 2;
	rot->rx -= twoPI * floor(rot->rx / twoPI);
	rot->ry -= twoPI * floor(rot->ry / twoPI);
	rot->rz -= twoPI * floor(rot->rz / twoPI);
}

static void	handle_rotation_keys(int keycode, t_mlx *mlx)
{
	double speed;

	speed = ROTATION_SPEED;
	if (keycode == KEY_O)
		mlx->map->rot.rx += speed;
	else if (keycode == KEY_P)
		mlx->map->rot.rx -= speed;
	else if (keycode == KEY_L)
		mlx->map->rot.ry += speed;
	else if (keycode == KEY_K)
		mlx->map->rot.ry -= speed;
	else if (keycode == KEY_M)
		mlx->map->rot.rz += speed;
	else if (keycode == KEY_N)
		mlx->map->rot.rz -= speed;
	round_rotation(&mlx->map->rot);
}

static int	key_hook(int keycode, t_mlx *mlx)
{
	//printf("Keycode: %d\n", keycode);
	if (keycode == KEY_ESC)
		stop_loop(mlx);
	handle_zoom_keys(keycode, mlx);
	handle_translation_keys(keycode, mlx);
	handle_rotation_keys(keycode, mlx);
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
