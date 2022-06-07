/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:20 by apigeon           #+#    #+#             */
/*   Updated: 2022/06/07 20:15:16 by apigeon          ###   ########.fr       */
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

# define WIN_HEIGHT	700
# define WIN_WIDTH	1000
# define WIN_TITLE	"FDF"

# define ABS(X) (((X) < 0) ? (-(X)) : (X))

# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF

# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17

# define KEY_ESC 65307

# define MOUSE_CLICK 1
# define MOUSE_MIDDLE_CLICK 2
# define MOUSE_RIGHT_CLICK 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define MASK_NO_EVENT 0L
# define MASK_KEY_PRESS 1L << 0

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_img;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
}               t_mlx;


typedef struct s_point
{
    int x;
    int y;
}               t_point;

typedef struct  s_map
{
    int **map;
    int x_len;
    int y_len;
}               t_map;

int     error(char *message, int code);
void    setup_hooks(t_mlx *mlx);
t_map   *parse_file(char *filename);
t_list	*read_file(char *filename);
void	draw_line(t_img *img, t_point a, t_point b, int color);


#endif
