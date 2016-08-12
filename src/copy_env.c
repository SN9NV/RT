/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 13:16:30 by rojones           #+#    #+#             */
/*   Updated: 2016/08/12 18:26:21 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_env	*copy_env(t_env *e)
{
	t_env	*res;

	res = (t_env *)malloc(sizeof(t_env));
	res->win = e->win;
	res->rend = e->rend;
	res->img = e->img;
	res->px = e->px;
	res->px_pitch = e->px_pitch;
	res->ray = e->ray;
	res->camera = e->camera;
	res->p_hit = e->p_hit;
	res->prim = e->prim;
	res->prims = e->prims;
	res->o_hit = e->o_hit;
	res->object = e->object;
	res->objects = e->objects;
	res->light = e->light;
	res->lights = e->lights;
	res->material = e->material;
	res->materials = e->materials;
	res->t = e->t;
	res->maxdepth = e->maxdepth;
	return (res);
}