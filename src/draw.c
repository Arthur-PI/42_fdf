/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:59:21 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/07 20:36:06 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;
	//char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		offset = (y * img->line_length + (x * img->bits_per_pixel / 8));
		//dst = img->addr + offset;
		img->addr[offset] = color;
		img->addr[++offset] = color >> 8;
		img->addr[++offset] = color >> 16;
	}
}

// (0,700) (1000,0)
// dx = 1000
// dy = -700
static void	bresenham_up(t_img *img, t_point a, t_point b, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	dx = b.x - a.x;
	dy = a.y - b.y;
	p = 2 * (dy - dx);
	x = a.x;
	y = a.y;
	while (x < b.x && y > b.y)
	{
		img_pixel_put(img, x, y, color);
		printf("(%d,%d)\n", x, y);
		if (p <= 0)
		{
			p += 2 * dy;
			x++;
		}
		if (p >= 0)
		{
			p -= 2 * dx;
			y--;
		}
	}
}

static void	bresenham_down(t_img *img, t_point a, t_point b, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	dx = b.x - a.x;
	dy = b.y - a.y;
	p = 2 * (dy - dx);
	x = a.x;
	y = a.y;
	while (x < b.x && y < b.y)
	{
		img_pixel_put(img, x, y, color);
		if (p <= 0)
		{
			p += 2 * dy;
			x++;
		}
		if (p >= 0)
		{
			p -= 2 * dx;
			y++;
		}
	}
}

void	draw_line(t_img *img, t_point a, t_point b, int color)
{
	if (a.x < b.x && a.y < b.y)
		bresenham_down(img, a, b, color);
	else if (a.x > b.x && a.y > b.y)
		bresenham_down(img, b, a, color);
	else if (a.x < b.x && a.y > b.y)
		bresenham_up(img, a, b, color);
	else if (a.x > b.x && a.y < b.y)
		bresenham_up(img, b, a, color);
}
