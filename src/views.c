/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   views.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:59:18 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 21:04:10 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_view(t_map *map)
{
	copy_map(map->map, map->map_copy, map->x_len, map->y_len);
	translate_map(map, -(WIN_WIDTH / 2), -(WIN_HEIGHT / 2));
	rotate_map(map, M_PI / 6, X_AXIS);
	rotate_map(map, -M_PI / 6, Y_AXIS);
	rotate_map(map, M_PI / 10, Z_AXIS);
	zoom_map(map, 0.7);
}

void	para_view(t_map *map)
{
	copy_map(map->map, map->map_copy, map->x_len, map->y_len);
	translate_map(map, -(WIN_WIDTH / 2), -(WIN_HEIGHT / 2));
	zoom_map(map, 0.7);
}
