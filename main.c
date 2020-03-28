/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ecelsa <ecelsa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:09:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/28 17:42:12 by Ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <limits.h>

#define W 600
#define H 600

int Cw = 600, Ch = 600;
// double VxMin = -0.15, VxMax = 0.05;
// double VyMin = 0.85, VyMax = 0.93;

double VxMin = -2, VxMax = 2;
double VyMin = -2, VyMax = 2;
int coef = 80;
int bn(double n, double l, double r)
{
	return(n>l && n<=r);
}

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
	(void)r;
	(void)g;
	(void)b;
	double d = 0;
	while (iter < n && fabs(c) < 4)
	{
		iter++;
		d = z.x * z.x - z.y * z.y + re;
		z.y = 2 * z.x * z.y + im;
		z.x = d;
		c = z.x - z.y;
	}

	double t = (double)iter / (double)n;
	r = (int)(9 * (1 - t) * pow(t, 3) * 255);
	g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(8.5 * pow((1 - t), 4) * t * 255);
	return (rgba(r,g,b,0));
	/*int col;
	if (bn(с,0,7))
		col = rgba(coef*с,0,0,0);
	else if (bn(c,7,14))
		col = rgba(coef*c,coef*c,0,0);
	else if (bn(c,14,21))
		col = rgba(coef*c,0,coef*c,0);
	else if (bn(c,21,28))
		col = rgba(0,coef*c,0,0);
	else if (bn(c,28,35))
		col = rgba(coef*c,coef*c,0,0);
	else if (bn(c,35,42))
		col = rgba(0,coef*c,coef*c,0);
	else if (bn(c,42,49))
		col = rgba(0,0,coef*c,0);
	else if (bn(c,49,56))
		col = rgba(coef*c,0,coef*c,0);
	else if (bn(c,56,64))
		col = rgba(0,coef*c,coef*c,0);
	else col = 0;
	return (col);*/
	/*c = ((double)255 / n);
	r = c * iter;
	g = (255 - (c * iter));
	b = (c * iter);
	//return(iter);
	return (rgba(0, 0, b, 0));*/
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
				iter = rgba(0,0,0,0);
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

	//mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img_ptr, 0, 0);
	mlx_hook(win.win_ptr, 4, (1L<<2), mouse_press, &win);
	mlx_hook(win.win_ptr, 5, (1L<<3), mouse_release, &win);
    mlx_hook(win.win_ptr, 6, (1L<<13), mouse_move, &win);
	mlx_hook(win.win_ptr, 2, 1, key_press, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}