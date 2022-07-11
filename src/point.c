/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:39:15 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 19:19:50 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_point	get_map_point(t_point p, double offset)
{
	t_point newp;

	newp.x = p.x * offset;
	newp.y = p.y * offset;
	newp.z = p.z * 5;
	newp.color = p.color;
	return (newp);
}

t_point	get_point(int x, int y, int z, int color)
{
	t_point	point;

	(void)color;
	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}

t_point copy_point(t_point p)
{
	return get_point(p.x, p.y, p.z, p.color);
}
