/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:54:46 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 16:12:47 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_H
# define CONSTANT_H

# define WIN_HEIGHT 900
# define WIN_WIDTH 1200
# define WIN_TITLE "FDF"

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define UP 1
# define DOWN -1

# define X_AXIS 1
# define Y_AXIS 2
# define Z_AXIS 3

# define ERROR 1
# define NO_ERROR 0

# define COLOR_1 0x000A46D1
# define COLOR_2 0x004DE94C
# define COLOR_3 0x00FFEE00
# define COLOR_4 0x00FF8C00
# define COLOR_5 0x00F60000

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
# define KEY_O 111
# define KEY_P 112
# define KEY_K 107
# define KEY_L 108
# define KEY_N 110
# define KEY_M 109
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
# define MASK_KEY_PRESS 1L

# define TRANSLATION_SPEED 20
# define ZOOM_SPEED 0.05
# define ROTATION_SPEED 0.1

# ifndef BOOL_H
#  define TRUE 1
#  define FALSE 0
# endif

#endif
