/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:18:29 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:39:03 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_color(t_map *map)
{
	int		x;
	int		y;
	t_point	*p;

	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			p = &map->map[y][x];
			p->color = generate_color(p->z, map->z_range[0], map->z_range[1]);
			x++;
		}
		y++;
	}
}
