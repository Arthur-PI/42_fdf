/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:20 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/13 22:30:21 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <X11/X.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"
# include "constant.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_point;

typedef struct s_point2d
{
	int	x;
	int	y;
	int	color;
}				t_point2d;

typedef struct s_map
{
	int		x_len;
	int		y_len;
	int		z_range[2];
	double	offset;
	double	offset_z;
	t_point	**map;
	t_point	**map_copy;
}				t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_map	*map;
}				t_mlx;

/*  Parsing, file reading and mlx stuff  */
void		init_mlx(t_mlx *mlx);
t_img		*get_image(t_mlx *mlx);
t_list		*read_file(char *filename);
t_map		*parse_file(char *filename);

/*  Points  */
t_point		copy_point(t_point p);
t_point		get_map_point(t_point p, t_map *map);
t_point		get_point(double x, double y, double z, int color);
t_point2d	get_point2d(t_point p);

/*  Map stuff  */

void		draw_map(t_mlx *mlx);
void		each(t_map *map, double *v, void (*f)(t_point *, double, double));
t_point		**malloc_map(int x_len, int y_len);
t_point		**copy_map(t_point **new_map, t_point **map, int x_len, int y_len);

/*  Errors  */

int			error(char *message, int code);
void		emergency_read_exit(t_list **lst, int fd);

/*  Free  */

void		free_map(t_map **map);
void		free_split(void *data);
void		free_image(t_mlx *mlx, t_img *img);
void		free_map_points(t_point **map, int y_len);

/*  Rotation, Translation, Zoom, and views  */

void		iso_view(t_map *map);
void		para_view(t_map *map);
void		zoom_map(t_map *map, double coef);
void		rotate_map(t_map *map, double angle, int axis);
void		translate_map(t_map *map, double tx, double ty);

/*  Color */

void		set_map_color(t_map *map);
int			blend_colors(int c1, int c2, double coef);
int			generate_color(int z, int min_z, int max_z);

/*  Draw and rendering stuff  */

void		print_map(t_map *map);
void		draw_line(t_mlx *mlx, t_point a, t_point b);
int			render(t_mlx *mlx);

/*  Hooks and handlers  */

void		setup_hooks(t_mlx *mlx);
void		handle_zoom_keys(int keycode, t_mlx *mlx);
void		handle_view_keys(int keycode, t_mlx *mlx);
void		handle_rotation_keys(int keycode, t_mlx *mlx);
void		handle_translation_keys(int keycode, t_mlx *mlx);

/*  Math functions  */

int			ft_abs(int x);
int			ft_min(int a, int b);
int			ft_max(int a, int b);

#endif
