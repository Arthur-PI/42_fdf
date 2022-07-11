/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:39:15 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 12:09:36 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_point(int x, int y, int z, int color)
{
	t_point	point;

	(void)color;
	point.x = x;
	point.y = y;
	point.z = z;
	if (z > 5)
		point.color = RED;
	else
		point.color = BLUE;
	return (point);
}

t_point copy_point(t_point p)
{
	return get_point(p.x, p.y, p.z, p.color);
}

void	rotate_point(t_point *p, t_rotation rot)
{
	t_point po;

	po = copy_point(*p);
	p->y = cos(rot.rx) * po.y - sin(rot.rx) * po.z;
	p->z = cos(rot.rx) * po.z + sin(rot.rx) * po.y;

	po = copy_point(*p);
	p->z = cos(rot.ry) * po.z - sin(rot.ry) * po.x;
	p->x = cos(rot.ry) * po.x + sin(rot.ry) * po.z;

	po = copy_point(*p);
	p->x = cos(rot.rz) * po.x - sin(rot.rz) * po.y;
	p->y = cos(rot.rz) * po.y + sin(rot.rz) * po.x;
}
