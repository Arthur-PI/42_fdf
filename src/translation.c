/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:56:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 19:16:38 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	foreach_point(t_map *map, double val, void (*f)(t_point *, double))
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			f(&map->map[y][x], val);
			x++;
		}
		y++;
	}
}

void	translate_x(t_point *p, double tx)
{
	p->x += tx;
}

void	translate_y(t_point *p, double ty)
{
	p->y += ty;
}

void	rotate_x(t_point *p, double rx)
{
	t_point	op;

	op = copy_point(*p);
	printf("%f ; %f ; %f\n", rx, op.y, op.z);
	p->y = cos(rx) * op.y - sin(rx) * op.z;
	p->z = cos(rx) * op.z + sin(rx) * op.y;
}

void	rotate_y(t_point *p, double ry)
{
	t_point	op;

	op = copy_point(*p);
	p->z = cos(ry) * op.z - sin(ry) * op.x;
	p->x = cos(ry) * op.x + sin(ry) * op.z;
}

void	rotate_z(t_point *p, double rz)
{
	t_point	op;

	op = copy_point(*p);
	p->x = cos(rz) * op.x - sin(rz) * op.y;
	p->y = cos(rz) * op.y + sin(rz) * op.x;
}

void	zoom(t_point *p, double coef)
{
	p->x *= coef;
	p->y *= coef;
	p->z *= coef;
}
