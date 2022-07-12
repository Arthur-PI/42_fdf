/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:38:45 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 10:08:11 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(t_point *p, double cosAngle, double sinAngle)
{
	t_point	op;

	op = copy_point(*p);
	p->y = cosAngle * op.y - sinAngle * op.z;
	p->z = cosAngle * op.z + sinAngle * op.y;
}

static void	rotate_y(t_point *p, double cosAngle, double sinAngle)
{
	t_point	op;

	op = copy_point(*p);
	p->z = cosAngle * op.z - sinAngle * op.x;
	p->x = cosAngle * op.x + sinAngle * op.z;
}

static void	rotate_z(t_point *p, double cosAngle, double sinAngle)
{
	t_point	op;

	op = copy_point(*p);
	p->x = cosAngle * op.x - sinAngle * op.y;
	p->y = cosAngle * op.y + sinAngle * op.x;
}

void	rotate_map(t_map *map, double angle, int axis)
{
	double	cos_sin[2];

	cos_sin[0] = cos(angle);
	cos_sin[1] = sin(angle);
	if (axis == X_AXIS)
		foreach(map, cos_sin, &rotate_x);
	else if (axis == Y_AXIS)	
		foreach(map, cos_sin, &rotate_y);
	else if (axis == Z_AXIS)
		foreach(map, cos_sin, &rotate_z);
}
