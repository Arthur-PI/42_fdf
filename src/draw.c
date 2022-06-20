/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:59:21 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/20 15:49:46 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;

	if (x >= 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		offset = (y * img->line_length + (x * img->bits_per_pixel / 8));
		img->addr[offset] = color;
		img->addr[++offset] = color >> 8;
		img->addr[++offset] = color >> 16;
	}
}

static void	bresenham(t_img *img, t_point a, t_point b, int *signs)
{
	int	dx;
	int	dy;
	int	p;
	int	p2;

	dx = ABS(b.x - a.x);
	dy = -ABS(b.y - a.y);
	p = dx + dy;
	while (1)
	{
		img_pixel_put(img, a.x, a.y, (a.color + b.color) / 2);
		if (a.x == b.x && a.y == b.y)
			break ;
		p2 = 2 * p;
		if (p2 >= dy)
		{
			p += dy;
			a.x += signs[0];
		}
		if (p2 <= dx)
		{
			p += dx;
			a.y += signs[1];
		}
	}
}

void	draw_line(t_img *img, t_point a, t_point b)
{
	int	signs[2];

	signs[0] = UP;
	signs[1] = UP;
	if (a.x > b.x)
		signs[0] = DOWN;
	if (a.y > b.y)
		signs[1] = DOWN;
	bresenham(img, a, b, signs);
}
