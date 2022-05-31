/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:57:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/05/31 18:06:29 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		exit(error("Error: wrong filename extension", 1));
	if (ft_strncmp(filename + (len - 4), ".fdf", 4) != 0)
		exit(error("Error: wrong filename extension", 1));
	return (1);
}

static t_list	*read_file(char *filename)
{
	int		fd;
	char	*line;
	t_list	*lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		close(fd);
		exit(error("Error: can't open or read the file", 1));
	}
	lines = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	get_x_len(t_list *lst)
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

int	get_y_len(t_list *lst)
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

int	fill_map(t_map *map, t_list *lines)
{
	int		x;
	int		y;
	char	**numbers_char;

	y = 0;
	while (lines)
	{
		numbers_char = ft_split(lines->content, ' ');
		lines = lines->next;
		x = 0;
		map->map[y] = malloc(map->x_len * sizeof(int));
		// TODO malloc protection
		while (x < map->x_len)
		{
			map->map[y][x] = ft_atoi(numbers_char[x]);
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

	valid_filename(filename);
	lines = read_file(filename);
	map = malloc(sizeof(*map));
	if (!map)
	{
		ft_lstclear(&lines, &free);
		exit(error("Error: wrog malloc", 1));
	}
	map->x_len = get_x_len(lines);
	map->y_len = get_y_len(lines);
	map->map = malloc(map->y_len * sizeof(*map->map));
	if (!map->map)
		exit(error("Error: Malloc allocation error during parsing", 1));
	fill_map(map, lines);
	ft_lstclear(&lines, &free);
	return (map);
}
