/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:21:24 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 22:09:16 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error(char	*message, int code)
{
	ft_printf("Error: %s\n", message);
	return (code);
}

void	emergency_read_exit(t_list **lst, int fd)
{
	ft_lstclear(lst, &free_split);
	close(fd);
	exit(error("malloc allocation error happened during file read", 1));
}
