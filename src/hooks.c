/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:37:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/02 21:08:36 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	quit(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

static int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		quit(mlx);
	return (0);
}

void	setup_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, ON_DESTROY, MASK_NO_EVENT, quit, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, MASK_KEY_PRESS, key_hook, mlx);
}
