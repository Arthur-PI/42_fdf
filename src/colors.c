/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:11:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:29:21 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

static double	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

static double	get_b(int color)
{
	return (color & 0xFF);
}

int	blend_colors(int c1, int c2, double coef)
{
	int		cnew;
	double	icoef;

	icoef = 1 - coef;
	cnew = 0;
	cnew = (int)(get_r(c1) * coef + get_r(c2) * icoef) << 8;
	cnew = (int)(cnew + (get_g(c1) * coef + get_g(c2) * icoef)) << 8;
	cnew = (int)(cnew + (get_b(c1) * coef + get_b(c2) * icoef));
	return (cnew);
}

int	generate_color(int z, int min_z, int max_z)
{
	int	x;
	int	color;
	int	c[6];

	c[0] = COLOR_1;
	c[1] = COLOR_2;
	c[2] = COLOR_3;
	c[3] = COLOR_4;
	c[4] = COLOR_5;
	c[5] = COLOR_5;
	if (min_z < 0)
		z -= min_z;
	x = (max_z - min_z) / 5;
	if (x == 0)
		return (c[3]);
	color = z / x;
	color = blend_colors(c[color], c[color + 1], 1 - ((double)(z % x) / x));
	return (color);
}
