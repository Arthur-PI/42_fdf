/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:59:21 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/02 21:19:09 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	bresenham(t_img *img, t_point a, t_point b, int color)
{
	int	dx;
	int	dy;
	int	p;
	int	x;
	int	y;

	dx = b.x - a.x;
	dy = b.y - a.x;
	x = a.x;
	y = a.y;
	p = 2 * dy - dx;
	while (x < b.x)
	{
		img_pixel_put(img, x, y, color);
		p += 2 * dy;
		if (p >= 0)
		{
			y++;
			p -= 2 * dx;
		}
		else
			x++;
	}
}
