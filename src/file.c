/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:41:54 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/02 21:16:55 by apigeon          ###   ########.fr       */
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

static void	emergency_read_exit(t_list **lst, int fd)
{
	ft_lstclear(lst, &free);
	close(fd);
	exit(error("Error: malloc allocation error happened", 1));
}

t_list	*read_file(char *filename)
{
	int		fd;
	char	*line;
	t_list	*lines;
	t_list	*tmp;

	valid_filename(filename);
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
		tmp = ft_lstnew(line);
		if (!tmp)
			emergency_read_exit(&lines, fd);
		ft_lstadd_back(&lines, tmp);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}
