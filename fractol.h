/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:14:17 by ecelsa            #+#    #+#             */
/*   Updated: 2020/03/05 22:52:34 by ecelsa           ###   ########.fr       */
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


#endif
