/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:18:29 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 22:18:56 by apigeon          ###   ########.fr       */
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

t_point	**copy_map(t_point **new_map, t_point **map, int x_len, int y_len)
{
	int		x;
	int		y;

	y = 0;
	while (y < y_len)
	{
		x = 0;
		while (x < x_len)
		{
			new_map[y][x] = map[y][x];
			x++;
		}
		y++;
	}
	return (new_map);
}

void	free_map_points(t_point **map, int y_len)
{
	int	y;

	y = 0;
	while (y < y_len)
		free(map[y++]);
	free(map);
}

t_point	**malloc_map(int x_len, int y_len)
{
	int		y;
	t_point	**map;

	map = malloc(y_len * sizeof(*map));
	if (!map)
		return (NULL);
	y = 0;
	while (y < y_len)
	{
		map[y] = malloc(x_len * sizeof(*map[y]));
		if (!map[y])
		{
			free_map_points(map, y_len);
			return (NULL);
		}
		y++;
	}
	return (map);
}
