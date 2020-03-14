/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:09:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/14 22:43:20 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <limits.h>

#define W 1920
#define H 1080

int Cw = 1920, Ch = 1080;
// double VxMin = -0.15, VxMax = 0.05;
// double VyMin = 0.85, VyMax = 0.93;

double VxMin = -2, VxMax = 1;
double VyMin = -1, VyMax = 1;


void	uput_pixel(int *img, int x, int y, int color)
{
	if ((x >= 0 && x < Cw) && (y >= 0 && y < Ch))
 		img[y * Cw + x] = color;
}

void	put_pixel(int *img, int x, int y, int color)
{
	uput_pixel(img, x + (Cw / 2), y + (Ch / 2), color);
}

// c = x + i * y;
// Z(0) = 0;
// Z(1) = sqr(Z(0)) + c = x+i*y;
// Z(2) = sqr(Z(1)) + c = 0 + sqr(x+i*y) + x+i*y = x2 + 2ixy -y2 + x + iy
// Z(2) = sqr(Z(1)) + c = 0 + sqr(x+i*y) + 

typedef unsigned char uchar;

typedef struct	s_complex
{
	double	x;
	double	y;
}				t_complex;


//void grid (int *img,)

int iterZ(double re, double im, int n)
{
	int r,g,b;
	int iter;
	double c;
	t_complex z;
	c = re - im;
	z.x = re;
	z.y = im;
	iter = 0;
	double d = 0;
	while (iter < n && fabs(c) < 4)
	{
		iter++;
		d = z.x * z.x - z.y * z.y + re;
		z.y = 2 * z.x * z.y + im;
		z.x = d;
		c = z.x - z.y;
	}
	c = ((double)255 / n);
	r = c * iter;
	g = (255 - (c * iter));
	b = (c * iter);
	//return(iter);
	return (rgba(0, 0, b, 0));
}

void draw_mandelbort(t_window *win)
{
	double im = VyMax;
	double re = VxMin;
	double dVh = (VyMax - VyMin) / Ch;
	double dVw = (VxMax - VxMin) / Cw;
	int		x,y;
	int		iter;


	if (dVw == 0)
		printf("Zero\n");
	while (im >= VyMin)
	{
		re = VxMin;
		while (re <= VxMax)
		{
			// iter = iterZ(re, im, win->iter);
			if (hm(re, im) == 1)
				iter = rgba(0,0,255,0);
			else
				iter = iterZ(re, im, win->iter);
			x = (re - VxMin) / dVw;
			y = (VyMax - im) / dVh;
			
				// if (((re - VxMin) / dVw) == (re - VxMin) / dVw * )
				// {
				// 	x = 0;
				// 	iter = rgba(255,0,0,0);
				// }
			uput_pixel(win->img[0], x, y, iter);
			re += dVw;
		}
		im -= dVh;
	}
}

int		main(void)
{
	t_window	win;
	
	
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, Cw, Ch, "hop");
	win.img_ptr[0] = mlx_new_image(win.mlx_ptr, Cw, Ch);
	win.img[0] = (int*)mlx_get_data_addr(win.img_ptr[0], &win.bpp, &win.size_line, &win.endian);
	win.img_ptr[1] = mlx_new_image(win.mlx_ptr, Cw, Ch);
	win.img[1] = (int*)mlx_get_data_addr(win.img_ptr[1], &win.bpp, &win.size_line, &win.endian);
	win.iter = 5;
	win.btn_d = 0;
	draw_mandelbort(&win);

	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img_ptr, 0, 0);
	mlx_hook(win.win_ptr, 4, (1L<<2), mouse_press, &win);
	mlx_hook(win.win_ptr, 5, (1L<<3), mouse_release, &win);
    mlx_hook(win.win_ptr, 6, (1L<<13), mouse_move, &win);
	mlx_hook(win.win_ptr, 2, 1, key_press, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}