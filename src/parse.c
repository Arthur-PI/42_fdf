/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:57:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/10 22:34:37 by apigeon          ###   ########.fr       */
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
	free(map);
	return (-1);
}

static int	fill_map(t_map *map, t_list *lines)
{
	int		x;
	int		y;
	char	**numbers_char;

	y = 0;
	while (lines)
	{
		numbers_char = ft_split(lines->content, ' ');
		if (!numbers_char)
			return (emergency_fill_problem(map));
		lines = lines->next;
		x = 0;
		map->map[y] = malloc(map->x_len * sizeof(*map->map[y]));
		if (!map->map[y])
			return (emergency_fill_problem(map));
		while (x < map->x_len)
		{
			map->map[y][x] = get_point(x, y, ft_atoi(numbers_char[x]), BLUE);
			free(numbers_char[x]);
			x++;
		}
		free(numbers_char);
		y++;
	}
	return (1);
}

t_map	*parse_file(char *filename)
{
	t_list	*lines;
	t_map	*map;

	lines = read_file(filename);
	map = malloc(sizeof(*map));
	if (!map)
	{
		ft_lstclear(&lines, &free);
		exit(error("Error: malloc allocation problem", 1));
	}
	map->x_len = get_x_len(lines);
	map->y_len = get_y_len(lines);
	map->map = malloc(map->y_len * sizeof(*map->map));
	if (!map->map)
	{
		free(map);
		ft_lstclear(&lines, &free);
		exit(error("Error: Malloc allocation error during parsing", 1));
	}
	if (fill_map(map, lines) != 1)
		return (NULL);
	ft_lstclear(&lines, &free);
	ft_printf("Parsing done\n");
	return (map);
}
