/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:57:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 22:17:59 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_x_len(t_list *lst)
{
	int		i;
	char	**line;

	line = lst->content;
	i = 0;
	while (line[i])
		i++;
	return (i);
}

static int	get_y_len(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static int	fill_map(t_map *map, t_list *lines)
{
	int		x;
	int		y;
	int		z;
	char	**numbers_char;

	y = 0;
	while (lines)
	{
		numbers_char = (char **)lines->content;
		x = 0;
		while (x < map->x_len)
		{
			z = ft_atoi(numbers_char[x]);
			map->map[y][x] = get_map_point(get_point(x, y, z, 0), map);
			map->z_range[0] = ft_min(map->z_range[0], map->map[y][x].z);
			map->z_range[1] = ft_max(map->z_range[1], map->map[y][x].z);
			x++;
		}
		lines = lines->next;
		y++;
	}
	return (NO_ERROR);
}

static t_map	*init_map(t_list *lines)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	map->x_len = get_x_len(lines);
	map->y_len = get_y_len(lines);
	map->z_range[0] = 0;
	map->z_range[1] = 0;
	if (WIN_WIDTH / map->x_len > WIN_HEIGHT / map->y_len)
		map->offset = (double) WIN_HEIGHT / (double) map->y_len;
	else
		map->offset = (double) WIN_WIDTH / (double) map->x_len;
	map->offset_z = map->offset / 4;
	map->map = malloc_map(map->x_len, map->y_len);
	if (!map->map || fill_map(map, lines) == ERROR)
	{
		if (map->map)
			free_map_points(map->map, map->y_len);
		free(map);
		return (NULL);
	}
	return (map);
}

t_map	*parse_file(char *filename)
{
	t_list	*lines;
	t_map	*map;

	lines = read_file(filename);
	map = init_map(lines);
	if (map)
	{
		set_map_color(map);
		map->map_copy = malloc_map(map->x_len, map->y_len);
		if (!map->map_copy)
		{
			free_map_points(map->map, map->y_len);
			free(map);
			map = NULL;
		}
		else
			copy_map(map->map_copy, map->map, map->x_len, map->y_len);
	}
	ft_lstclear(&lines, &free_split);
	return (map);
}
