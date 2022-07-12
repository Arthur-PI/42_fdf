/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:21:24 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 15:19:20 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error(char	*message, int code)
{
	ft_printf("Error: %s\n", message);
	return (code);
}

int	emergency_fill_problem(t_map *map)
{
	int	y;

	y = 0;
	while (map->map[y])
		free(map->map[y++]);
	return (ERROR);
}
