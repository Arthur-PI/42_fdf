/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:41:54 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 22:06:57 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		exit(error("wrong filename extension", 1));
	if (ft_strncmp(filename + (len - 4), ".fdf", 4) != 0)
		exit(error("wrong filename extension", 1));
	return (1);
}

static int	open_file(char *filename)
{
	int	fd;

	valid_filename(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		close(fd);
		exit(error("can't open or read the file", 1));
	}
	return (fd);
}

static char	**read_line(int fd)
{
	char	*line;
	char	**line_split;

	line = get_next_line(fd);
	if (!line)
		return ((void *)FILE_OVER);
	line_split = ft_split(line, ' ');
	free(line);
	return (line_split);
}

void	free_split(void *data)
{
	int		i;
	char	**splits;

	splits = data;
	if (splits)
	{
		i = 0;
		while (splits[i])
			free(splits[i++]);
		free(splits);
	}
}

t_list	*read_file(char *filename)
{
	int		fd;
	char	**line_split;
	t_list	*start;
	t_list	*current;

	fd = open_file(filename);
	line_split = read_line(fd);
	if (!line_split)
		return (NULL);
	current = ft_lstnew(line_split);
	start = current;
	while (current && current->content != NULL)
	{
		line_split = read_line(fd);
		if (!line_split)
			emergency_read_exit(&start, fd);
		if (line_split == (void *)FILE_OVER)
			break ;
		ft_lstadd_back(&current, ft_lstnew(line_split));
		current = current->next;
		if (!current)
			emergency_read_exit(&start, fd);
	}
	close(fd);
	return (start);
}
