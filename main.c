/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:09:46 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/07 22:45:53 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int Cw = 1920, Ch = 1080;
int Vw = 1, Vh = 1;


void	uput_pixel(int *img, int x, int y, int color)
{
	if ((x <= Cw) && (y < Ch))
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

#define W 1920
#define H 1080
#define X0 (3*W/4)
#define Y0 (H/2)
#define L 320.0

typedef unsigned char uchar;

typedef struct	s_complex
{
	double	x;
	double	y;
}				t_complex;

uchar get_gray_color(t_complex z0)
{
	t_complex z = {0, 0};
	for (uchar gray = 255; gray; gray--)
	{
		//sgrt(z.x*z.x + z.y*z.y)
		if (sqrt(z.x*z.x + z.y*z.y) > 2)
			return gray;
		z.x = z.x * z.x - z.y * z.y + z0.x;
		z.y = 2 * z.x * z.y + z0.y;
	}
	return 0;
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
	for (int i = 0; i < W; i++)
	for (int j = 0; j < H; j++)
	{
		double x = (i - X0) / L;
		double y = (j - Y0) / L;
		t_complex z = {x, y};
		uchar gray = get_gray_color(z);
		if (gray != 255)
			put_pixel(img[0], i, j, rgba(gray, gray, gray, 0));
		//set_color(img[0], i, j, (color) {gray, gray, gray});
	}
	// put_pixel(img[0], 0, 0, sum_color(0xff00ff, 0xffff));
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr[0], 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}





// int main()
// {
// 	image *img = create_image(W, H);
// 	for (int i = 0; i < W; i++)
// 	for (int j = 0; j < H; j++)
// 	{
// 		double x = (i - X0) / L;
// 		double y = (j - Y0) / L;
// 		double complex z = x + I * y;
// 		uchar gray = get_gray_color(z);
// 		if (gray != 255)
// 		set_color(img, i, j, (color) {gray, gray, gray});
// 	}
// 	save_to_file(img, "out.bmp");
// 	free(img);
// 	return 0;
// }