/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:59:21 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/10 22:58:48 by apigeon          ###   ########.fr       */
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

void	offset(t_point *p, int offset)
{
	p->x = p->x * offset - WIN_WIDTH / 2;
	p->y = p->y * offset - WIN_HEIGHT / 2;
	p->z = p->z * 10;
}

void	apply_zoom(t_point *p, double zoom)
{
	p->x *= zoom;
	p->y *= zoom;
	p->z *= zoom;
}

void	translate(t_point *p, t_translate trans)
{
	p->x += trans.tx;
	p->y += trans.ty;
}

int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

int	blend_colors(int c1, int c2)
{
	int cnew;

	cnew = 0;
	cnew = ((get_r(c1) + get_r(c2)) / 2) << 8;
	cnew = (cnew + ((get_g(c1) + get_g(c2)) / 2)) << 8;
	cnew += (get_b(c1) + get_b(c2)) / 2;
	return (cnew);
}

void	draw_line(t_mlx *mlx, t_point x1, t_point x2)
{
	int	signs[2];
	t_point	a;
	t_point	b;

	a = copy_point(x1);
	b = copy_point(x2);
	offset(&a, mlx->img->offset);
	offset(&b, mlx->img->offset);
	rotate_point(&a, mlx->map->rot);
	rotate_point(&b, mlx->map->rot);
	apply_zoom(&a, mlx->map->zoom);
	apply_zoom(&b, mlx->map->zoom);
	translate(&a, mlx->map->trans);
	translate(&b, mlx->map->trans);
	signs[0] = UP;
	signs[1] = UP;
	if (a.x > b.x)
		signs[0] = DOWN;
	if (a.y > b.y)
		signs[1] = DOWN;
	a.color = blend_colors(a.color, b.color);
	bresenham(mlx->img, a, b, signs);
}
