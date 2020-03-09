/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:09:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/09 21:08:42 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define W 1920
#define H 1080

int Cw = 1920, Ch = 1080;
// double VxMin = -0.15, VxMax = 0.05;
// double VyMin = 0.85, VyMax = 0.93;

double VxMin = -2, VxMax = 1;
double VyMin = -1, VyMax = 1;

void	uput_pixel(int *img, int x, int y, int color)
{
	if ((x < Cw) && (y < Ch))
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

int iterZ(double re, double im)
{
	int n;
	int r,g,b;
	int iter;
	double c;
	t_complex z;
	c = re - im;
	z.x = re;
	z.y = im;
	iter = 0;
	n = 2048;
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
	b = fabs((c * iter) - 255);
	//return(iter);
	return (rgba(r, g, b ,0));
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr[2];
	int		*img[2];
	int		bpp;
	int		size_line;
	int		endian;
	int		iter;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, Cw, Ch, "hop");
	img_ptr[0] = mlx_new_image(mlx_ptr, Cw, Ch);
	img[0] = (int*)mlx_get_data_addr(img_ptr[0], &bpp, &size_line, &endian);
	iter = iterZ(-0.1, 0.1);
	iter = iterZ(-2, 1);
	double im = VyMax;
	double re = VxMin;
	double dVh = (VyMax - VyMin) / Ch;
	double dVw = (VxMax - VxMin) / Cw;
	int		x,y;
	while (im >= VyMin)
	{
		re = VxMin;
		while (re <= VxMax)
		{
			iter = iterZ(re, im);
			x = (re - VxMin) / dVw;
			y = (VyMax - im) / dVh;
			uput_pixel(img[0], x, y, iter);
			re += dVw;
		}
		im -= dVh;
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr[0], 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}