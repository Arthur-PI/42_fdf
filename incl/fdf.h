/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:20 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/10 16:17:04 by apigeon          ###   ########.fr       */
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

# include <stdio.h>

# define WIN_HEIGHT 900
# define WIN_WIDTH 1200
# define WIN_TITLE "FDF"

# define ABS(X) (((X) < 0) ? (-(X)) : (X))

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define UP 1
# define DOWN -1

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_ARROW_UP 65362
# define KEY_ARROW_DOWN 65364
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_RIGHT 65363

# define MOUSE_CLICK 1
# define MOUSE_MIDDLE_CLICK 2
# define MOUSE_RIGHT_CLICK 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define MASK_NO_EVENT 0L
# define MASK_KEY_PRESS 1L << 0

# define TRANSLATE_SPEED 10
# define ZOOM_SPEED 0.05

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
void	draw_line(t_img *img, t_point a, t_point b, t_rotation rot, t_translate trans, double zoom);
t_point get_point(int x, int y, int z, int color);
t_point copy_point(t_point p);
void    rotate_point(t_point *p, t_rotation rot);
void    draw_map(t_mlx *mlx);

#endif
