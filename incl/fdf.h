/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:20 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 14:10:00 by apigeon          ###   ########.fr       */
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

typedef struct  s_translate
{
    int tx;
    int ty;
}               t_translate;

typedef struct s_point
{
    int x;
    int y;
    int z;
	int	color;
}               t_point;

typedef struct  s_rotation
{
    double  rx;
    double  ry;
    double  rz;
}               t_rotation;

typedef struct  s_map
{
    t_point **map;
    int     x_len;
    int     y_len;
	int	    offset;
    double      zoom;
    t_rotation  rot;
    t_translate trans;
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
void    rotate_point(t_point *p, t_rotation rot);
void    draw_map(t_mlx *mlx);
t_img   get_image(t_mlx *mlx);

#endif
