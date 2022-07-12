/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:59:21 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 11:50:37 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;

	x += WIN_WIDTH / 2;
	y += WIN_HEIGHT / 2;
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		offset = (y * img->line_length + (x * img->bits_per_pixel / 8));
		img->addr[offset] = color;
		img->addr[++offset] = color >> 8;
		img->addr[++offset] = color >> 16;
	}
}

static void	bresenham(t_img *img, t_point2d a, t_point2d b, int *signs)
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
		img_pixel_put(img, a.x, a.y, a.color);
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

static int	line_in_window(t_point2d x1, t_point2d x2)
{
	int right_border;
	int left_border;
	int top_border;
	int bottom_border;

	right_border = 0 - WIN_WIDTH / 2;
	left_border = WIN_WIDTH / 2;
	top_border = 0 - WIN_HEIGHT / 2;
	bottom_border = WIN_HEIGHT / 2;
	if (x1.x < right_border && x2.x < right_border)
		return (FALSE);
	if (x1.x > left_border && x2.x > left_border)
		return (FALSE);
	if (x1.y < top_border && x2.y < top_border)
		return (FALSE);
	if (x1.y > bottom_border && x2.y > bottom_border)
		return (FALSE);
	return (TRUE);
}

void	draw_line(t_mlx *mlx, t_point x1, t_point x2)
{
	int			signs[2];
	t_point2d	a;
	t_point2d	b;

	a = get_point2d(x1);
	b = get_point2d(x2);
	signs[0] = UP;
	signs[1] = UP;
	if (a.x > b.x)
		signs[0] = DOWN;
	if (a.y > b.y)
		signs[1] = DOWN;
	a.color = blend_colors(a.color, b.color, 0.5);
	if (line_in_window(a, b))
		bresenham(mlx->img, a, b, signs);
}
