/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:33:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/12 21:18:17 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

extern int Cw, Ch;
double VxMin, VxMax, VyMin, VyMax;


int hm(double x, double y)
{
	double ro_c;
	double teta;
	double ro;
	
	ro = sqrt((x - 0.25) * (x - 0.25) + y * y);
	teta = atan2(y, x - 0.25);
	ro_c = 0.5 - 0.5 * cos(teta);
	return ((ro <= ro_c) ? 1 : 0);	
}

void line(int x0, int x1, int y0, int y1, int *img)
{
	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int error = 0;
	int deltaerr = (deltay + 1);
	int y = y0;
	int diry = y1 - y0;

	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	for (int x = x0; x <= x1; x++)
	{
		uput_pixel(img, x, y, 0x00fdfdfd);
		// plot(x,y);
		error += deltaerr;
		if (error >= (deltax + 1))
		{
			y = y + diry;
			error = error - (deltax + 1);
		}
	}
}

int		key_press(int key, t_window *win)
{
	// double dVh = (VyMax - VyMin) / Ch;
	// double dVw = (VxMax - VxMin) / Cw;
	// double mem;
	(void)win;
	if (key == ESC)
		exit(0);
	if (key == SPACE)
	{
		// int z = 50;
		// double hh = z /((double)Cw / Ch);
		// int	pstW = Cw/2;
		// int	pstH = Ch/2;		
		//int i = x - Cw/2 + 50; //xmin
		//x + Cw / 2 - z // xmax
		// y - Ch / 2 + hh // ymax
		// y + Ch / 2 - hh //ymin
		double xx = ,yy;
		VxMax -= fabs(0.02*VxMax);
		VxMin += fabs(0.02*VxMin);
		VyMax -= fabs(0.02*VyMax);
		VxMin += fabs(0.02*VyMax);
	}
 	if (key == PLUS)
	{
		win->iter += 5;
		printf("+ ");
	}
	if (key == MINUS)
	{
		win->iter -= ((win->iter > 5) ? 5 : win->iter);
		printf("- ");
	}
	printf("key - %d iter - %d\n",key, win->iter);
	draw_mandelbort(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr[0], 0, 0);
	return (0);
}


void draw(int x, int y, t_window *win)
{
	int z = 50;
	double hh = z /((double)Cw / Ch);
	ft_memset(win->img[1], 0xff, Cw* Ch * 4);
	for (int i = x - Cw/2 + 50; i < x + Cw / 2 - z; i++)
		uput_pixel(win->img[1],i,y - Ch / 2 + hh, 0x00ffffff);
	for (int i = x - Cw/2 + 50; i < x + Cw / 2 - z; i++)
		uput_pixel(win->img[1],i, y + Ch / 2 - hh, 0x00ffffff);
}

int mouse_move(int x, int y, void *param)
{
	t_window	*win;

	win = param;

	if (win->btn_d)
	{
		draw(x,y,win);
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr[1], 0, 0);
	}
	return (0);
}

int mouse_press(int button, int x, int y, void *param)
{
	t_window *win;
	double dVh = (VyMax - VyMin) / Ch;
	double dVw = (VxMax - VxMin) / Cw;
	(void)x;
	(void)y;
	int z = 50;
	//double hh = z /((double)Cw / Ch);

	win = (t_window*)param;
	if ((x > 0 && x < Cw) && (y > 0 && y < Ch))
	{
		if (button == 4) // +
		{
			double hh = z /((double)Cw / Ch);
			int	pstW = Cw/2;
			int	pstH = Ch/2;		
			//int i = x - Cw/2 + 50; //xmin
			//x + Cw / 2 - z // xmax
			// y - Ch / 2 + hh // ymax
			// y + Ch / 2 - hh //ymin
			VyMax = x + pstW - z;
			VxMin = x - pstW + 50;
			VyMax = y - pstH + hh;
			VyMin = y + pstH - hh;
		}
 		if (button == 1) // +
		{
			win->btn_d = 1;
			//line(x - Cw/2 + 50 ,x + Cw/2 -50, y - Ch/2 + 28 , y+ Ch/2 - 28,win->img[1]);
			// for (int i = x - Cw/2 + 50; i < x + Cw/2 -50; i++)
			// 	uput_pixel(win->img[1],i,y+ Ch/2 - 28, 0x0f0f0f);
				
			// for (int i = y - Ch/2 + 28; i < y+ Ch/2 - 28; i++)
			// 	uput_pixel(win->img[1],x - Cw/2 + 50,i, 0x0f0f0f);	
			
			// for (int i = y - Ch/2 + 28; i < y+ Ch/2 - 28; i++)
			// 	uput_pixel(win->img[1],y+ Ch/2 - 28,i, 0x0f0f0f);	
			// VxMin = (x - Cw / 2 + 50) * dVw;
			// VxMax = (x + Cw / 2 - 50) * dVw;
			// VyMin = (y + Ch / 2 - 28) * dVh;
			// VyMax = (y - Ch / 2 + 28) * dVh;
			// printf("Vx - %f Vh-%f x - %i y - %i  VxMin %f VxMax %f VyMin %f VyMax %f\n",dVw * x, dVh * y, x, y, VxMin, VxMax, VyMin, VyMax);
			// draw_mandelbort(win);

			
			// draw(x,y,win);
			// mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr[1], 0, 0);
			
			
			//mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		}
		if (button == 5 || button == 2) // -
		{
			// VxMin = (x - (double)Cw / 2 - 50) * dVw;
			// VxMax = (x + (double)Cw / 2 + 50) * dVw;
			// VyMin = (y + (double)Ch / 2 + 28) * dVh;
			// VyMax = (y - (double)Ch / 2 - 28) * dVh;
			printf("Vx - %f Vh-%f x - %i y - %i  VxMin %f VxMax %f VyMin %f VyMax %f\n",dVw * x, dVh * y, x, y, VxMin, VxMax, VyMin, VyMax);
		//	draw_mandelbort(win);
			mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		}
	}
	write(1, "!",1);
	printf("btn-%i x-%i y-%i\n",button, x, y);
	return (0);
}
int mouse_release(int button, int x, int y, void *param)
{
	t_window *win;
	win = (t_window*)param;
	if (button == 1)
	{
		win->btn_d = 0;
	}
	printf("--btn-%i x-%i y-%i\n",button, x, y);
	return (0);
}