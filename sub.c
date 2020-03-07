#include "fractol.h"

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
