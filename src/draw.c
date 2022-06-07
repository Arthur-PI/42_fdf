/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:59:21 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/07 21:13:36 by apigeon          ###   ########.fr       */
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

static void	bresenham(t_img *img, t_point a, t_point b, int sign)
{
	int		dx;
	int		dy;
	int		p;
	t_point	pos;

	dx = ABS(b.x - a.x);
	dy = ABS(b.y - a.y);
	p = (dy - dx);
	pos.x = a.x;
	pos.y = a.y;
	while (pos.x != b.x && pos.y != b.y)
	{
		img_pixel_put(img, pos.x, pos.y, (a.color + b.color) / 2);
		if (p <= 0)
		{
			p += dy;
			pos.x++;
		}
		if (p >= 0)
		{
			p -= dx;
			pos.y += sign;
		}
	}
}

void	draw_line(t_img *img, t_point a, t_point b)
{
	if (a.x < b.x && a.y < b.y)
		bresenham(img, a, b, DOWN);
	else if (a.x > b.x && a.y > b.y)
		bresenham(img, b, a, DOWN);
	else if (a.x < b.x && a.y > b.y)
		bresenham(img, a, b, UP);
	else if (a.x > b.x && a.y < b.y)
		bresenham(img, b, a, UP);
}
