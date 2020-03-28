/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:14:17 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/27 19:58:02 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

#include <stdio.h>

# define FRACTOL_H
# define WIDTH	800
# define HEIGHT	800

# include "./minilibxX11/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# include "ubuntu.h"

typedef unsigned char	t_uchar;

typedef struct	s_ptr
{
	double	x;
	double	y;
	double	z;
}				t_ptr;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr[2];
	int		*img[2];
	int		bpp;
	int		btn_d;
	int		size_line;
	int		endian;
	int		iter;
}				t_window;


unsigned int	sum_color(int color1, int color2);
unsigned int	rgba(t_uchar r, t_uchar g, t_uchar b, t_uchar alpha);
int				ft_abs(int i);
int				key_press(int key, t_window *win);
void			draw_mandelbort(t_window *win);
int				mouse_move(int x, int y, void *param);
int				mouse_press(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
void			uput_pixel(int *img, int x, int y, int color);
void			put_pixel(int *img, int x, int y, int color);
int				hm(double x, double y);

#endif
