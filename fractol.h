/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:14:17 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/07 18:21:43 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH	800
# define HEIGHT	800

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

typedef unsigned char	t_uchar;

typedef struct	s_ptr
{
	double	x;
	double	y;
	double	z;
}				t_ptr;

unsigned int	sum_color(int color1, int color2);
unsigned int	rgba(t_uchar r, t_uchar g, t_uchar b, t_uchar alpha);
int				 ft_abs(int i);

#endif
