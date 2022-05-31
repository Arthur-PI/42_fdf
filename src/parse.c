/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:57:55 by apigeon           #+#    #+#             */
/*   Updated: 2022/05/31 12:48:28 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*parse_file(char *filename)
{
	int		fd;
	int		size;
	char	*line;
	t_list	*lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(error("Error: can't open the file", 1));
	size = 0;
	lines = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		ft_printf("%s", line);
		size += 1;
	}
	ft_printf("Reading done\n");
	return (NULL);
}
