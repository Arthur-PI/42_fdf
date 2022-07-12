/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:56:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:59:58 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	each(t_map *map, double *v, void (*f)(t_point *, double, double))
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			f(&map->map[y][x], v[0], v[1]);
			x++;
		}
		y++;
	}
}

static void	translate(t_point *p, double tx, double ty)
{
	p->x += tx;
	p->y += ty;
}

void	translate_map(t_map *map, double tx, double ty)
{
	double	trans[2];

	trans[0] = tx;
	trans[1] = ty;
	each(map, trans, &translate);
}

static void	zoom(t_point *p, double coef, double vide)
{
	(void) vide;
	p->x *= coef;
	p->y *= coef;
	p->z *= coef;
}

void	zoom_map(t_map *map, double coef)
{
	double	val[2];

	val[0] = coef;
	val[1] = 0;
	each(map, val, &zoom);
}
