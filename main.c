/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:09:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/05 23:47:51 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int Cw = 1920, Ch = 1080;
int Vw = 1, Vh = 1;

unsigned int	sum_color(int color1, int color2)
{
	int		color;

	color = ((color1 & 0xff) + (color2 & 0xff) <
		0xff) ? ((color1 & 0xff) + (color2 & 0xff)) : 0xff;
	color |= ((color1 & 0xff) + (color2 & 0xff) <
		0xff00) ? ((color1 & 0xff00) + (color2 & 0xff00)) : 0xff00;
	color |= ((color1 & 0xff0000) + (color2 & 0xff0000) <
		0xff0000) ? ((color1 & 0xff0000) + (color2 & 0xff0000)) : 0xff0000;
	color |= ((color1 & 0xff000000) + (color2 & 0xff000000)) / 2;
	return (color);
}

unsigned int	rgba(t_uchar r, t_uchar g, t_uchar b, t_uchar alpha)
{
	int		ret;

	ret = alpha;
	ret <<= 8;
	ret |= r;
	ret <<= 8;
	ret |= g;
	ret <<= 8;
	ret |= b;
	return (ret);
}

int ft_abs(int i)
{
	return ((i >=0) ? (i) : -(i));
}

void	uput_pixel(int *img, int x, int y, int color)
{
	if ((x <= Cw) && (y < Ch))
 		img[y * Cw + x] = color;
}

void	put_pixel(int *img, int x, int y, int color)
{
	uput_pixel(img, x + (Cw / 2), y + (Ch / 2), color);
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
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, Cw, Ch, "hop");
	img_ptr[0] = mlx_new_image(mlx_ptr, Cw, Ch);
	img[0] = (int*)mlx_get_data_addr(img_ptr[0], &bpp, &size_line, &endian);
	put_pixel(img[0], 0, 0, sum_color(0xff00ff, 0xffff));
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr[0], 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}