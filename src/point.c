/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:39:15 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 16:04:19 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_map_point(t_point p, t_map *map)
{
	t_point	newp;

	newp.x = p.x * map->offset;
	newp.y = p.y * map->offset;
	newp.z = p.z * map->offset_z;
	newp.color = p.color;
	return (newp);
}

t_point	get_point(double x, double y, double z, int color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}

t_point	copy_point(t_point p)
{
	return (get_point(p.x, p.y, p.z, p.color));
}

t_point2d	get_point2d(t_point p)
{
	t_point2d	p2d;

	p2d.x = p.x;
	p2d.y = p.y;
	p2d.color = p.color;
	return (p2d);
}
