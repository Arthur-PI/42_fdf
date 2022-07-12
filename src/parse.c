/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:57:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 13:22:32 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_x_len(t_list *lst)
{
	int		i;
	int		nb_numbers;
	char	*line;

	i = 0;
	nb_numbers = 0;
	line = lst->content;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		while (line[i] && line[i] != ' ')
			i++;
		nb_numbers++;
		while (line[i] && line[i] == ' ')
			i++;
	}
	return (nb_numbers);
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

static int	emergency_fill_problem(t_map *map)
{
	int	y;

	y = 0;
	while (map->map[y])
		free(map->map[y++]);
	return (ERROR);
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
		numbers_char = ft_split(lines->content, ' ');
		if (!numbers_char)
			return (emergency_fill_problem(map));
		map->map[y] = malloc(map->x_len * sizeof(*map->map[y]));
		if (!map->map[y])
			return (emergency_fill_problem(map));
		x = 0;
		while (x < map->x_len)
		{
			z = ft_atoi(numbers_char[x]);
			map->map[y][x] = get_map_point(get_point(x, y, z, 0), map);
			map->z_range[0] = MIN(map->z_range[0], map->map[y][x].z);
			map->z_range[1] = MAX(map->z_range[1], map->map[y][x].z);
			free(numbers_char[x]);
			x++;
		}
		free(numbers_char);
		lines = lines->next;
		y++;
	}
	return (NO_ERROR);
}

t_map	*init_map(t_list *lines)
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
	map->offsetZ = map->offset / 4;
	map->map = malloc(map->y_len * sizeof(*map->map));
	if (!map->map || fill_map(map, lines) == ERROR)
	{
		if (map->map)
			free(map->map);
		free(map);
		return (NULL);
	}
	return map;
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
			//printf("Z: %3d -> %x\n", (int)p->z, p->color);
			x++;
		}
		y++;
	}
}

t_map	*parse_file(char *filename)
{
	t_list	*lines;
	t_map	*map;

	lines = read_file(filename);
	map = init_map(lines);
	if (map)
		set_map_color(map);
	ft_lstclear(&lines, &free);
	ft_printf("Parsing done\n");
	return (map);
}
