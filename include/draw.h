/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 11:01:32 by adippena          #+#    #+#             */
/*   Updated: 2016/07/30 12:06:19 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "rt.h"

typedef struct	s_camera_ray
{
	t_vector	n;
	t_vector	u;
	t_vector	v;
	t_vector	l;
	t_vector	c;
//	t_camera	cam;
	double		d;
//	double		x_inc;
//	double		y_inc;
	double		w;
	double		h;
}				t_camera_ray;

#endif
