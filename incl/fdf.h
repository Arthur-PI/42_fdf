/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:20 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 19:05:07 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <X11/X.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"
# include "constant.h"

# include <stdio.h>
# include <string.h>

# define ABS(X) (((X) < 0) ? (-(X)) : (X))

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     offset;
}               t_img;

typedef struct s_point
{
    double x;
    double y;
    double z;
	int	color;
}               t_point;

typedef struct  s_map
{
    int         x_len;
    int         y_len;
	double	    offset;
    t_point     **map;
}               t_map;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   *img;
    t_map   *map;
}               t_mlx;

int     error(char *message, int code);
void    setup_hooks(t_mlx *mlx);
t_map   *parse_file(char *filename);
t_list	*read_file(char *filename);
void	draw_line(t_mlx *mlx, t_point a, t_point b);
t_point get_point(int x, int y, int z, int color);
t_point copy_point(t_point p);
void    draw_map(t_mlx *mlx);
t_img   get_image(t_mlx *mlx);
t_point get_map_point(t_point p, double offset);
void	foreach_point(t_map *map, double val, void (*f)(t_point *, double));
void	translate_x(t_point *p, double tx);
void	translate_y(t_point *p, double ty);
void	rotate_x(t_point *p, double rx);
void	rotate_y(t_point *p, double ry);
void	rotate_z(t_point *p, double rz);
void    zoom(t_point *p, double coef);
int     blend_colors(int c1, int c2);
void    print_map(t_map *map);
void    render(t_mlx *mlx);

#endif
