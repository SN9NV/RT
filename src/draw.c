/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <angusdippenaar@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 14:00:07 by adippena          #+#    #+#             */
/*   Updated: 2016/08/29 17:13:27 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/*
** l = ref[l]ect colour
** r = ref[r]act colour
*/

static uint32_t	find_colour(t_env *e)
{
	t_colour	c;
	t_colour	l;
	t_colour	r;
	t_material	*mat;

	c = (e->hit_type == FACE) ? face_diffuse(e) : prim_diffuse(e);
	mat = (e->hit_type == FACE) ?
		e->material[e->object_hit->material] :
		e->material[e->p_hit->material];
	l = mat->reflect > 0.0 ? reflect(e, 1) : (t_colour){0.0, 0.0, 0.0, 0.0};
	if (mat->refract > 0.0)
	{
		r = refract(e, 1, c);
		c.r = (c.r * (1 - mat->refract)) + (r.r * mat->refract);
		c.g = (c.g * (1 - mat->refract)) + (r.g * mat->refract);
		c.b = (c.b * (1 - mat->refract)) + (r.b * mat->refract);
	}
	return ((uint32_t)(
	(int)(((c.r * (1 - mat->reflect)) + (l.r * mat->reflect)) * 255.0) << 16 |
	(int)(((c.g * (1 - mat->reflect)) + (l.g * mat->reflect)) * 255.0) << 8 |
	(int)(((c.b * (1 - mat->reflect)) + (l.b * mat->reflect)) * 255.0)));
}

static uint32_t	find_base_colour(t_env *e)
{
	t_colour	c;

	if (!e->hit_type)
		return (0x7F7F7F);
	c = (e->hit_type == FACE) ? face_diffuse(e) : prim_diffuse(e);
	return ((uint32_t)(
	(unsigned int)(c.r * 255.0) << 16 |
	(unsigned int)(c.g * 255.0) << 8 |
	(unsigned int)(c.b * 255.0)));
}

static void		*draw_chunk(void *q)
{
	t_chunk		*c;
	uint32_t	*px;

	c = (t_chunk *)q;
	c->stopx = c->d.x + c->d.w;
	c->stopy = c->d.y + c->d.h;
	while (c->d.y < (int)c->e->y && c->d.y < c->stopy)
	{
		c->x = c->d.x;
		px = &c->e->px[c->d.y * c->e->x + c->d.x];
		while (c->x < (int)c->e->x && c->x < c->stopx)
		{
			c->e->p_hit = NULL;
			get_ray_dir(c->e, (double)c->x, (double)c->d.y);
			intersect_scene(c->e);
			*px++ = (c->e->p_hit && !c->e->p_hit->s_bool && !c->e->key.g) ?
				find_colour(c->e) : find_base_colour(c->e);
			++c->x;
		}
		++c->d.y;
	}
	SDL_UpdateWindowSurface(c->e->win);
	free(c->e);
	free(c);
	pthread_exit(0);
}

static void		make_chunks(t_env *e, SDL_Rect *d)
{
	t_make_chunks	m;

	m.tids = ceil((double)d->w / 64.0) * ceil((double)d->h / 64.0);
	m.tid = (pthread_t *)malloc(sizeof(pthread_t) * m.tids);
	m.thread = 0;
	m.chunk_y = 0;
	while (m.chunk_y * 64 < (size_t)d->h)
	{
		m.chunk_x = 0;
		while (m.chunk_x * 64 < (size_t)d->w)
		{
			m.c = (t_chunk *)malloc(sizeof(t_chunk));
			m.c->e = copy_env(e);
			m.c->d = (SDL_Rect){m.chunk_x * 64, m.chunk_y * 64, 64, 64};
			pthread_create(&m.tid[m.thread++], NULL, draw_chunk, (void *)m.c);
			++m.chunk_x;
		}
		++m.chunk_y;
	}
	while (m.thread--)
		pthread_join(m.tid[m.thread], NULL);
	free(m.tid);
}

static void		half_bytes(SDL_Surface *s)
{
	size_t			index;
	unsigned char	*px;

	index = s->h * s->pitch;
	px = (unsigned char *)(s->pixels + index - 1);
	while (index--)
		*px-- >>= 1;
}

void			draw(t_env *e, SDL_Rect d)
{
	time_t	t;

	if (e->s_num && !e->key.g)
	{
		half_bytes(e->img);
		SDL_UpdateWindowSurface(e->win);
	}
	t = time(NULL);
	setup_camera_plane(e);
	make_chunks(e, &d);
	if (!e->s_num)
	{
		t = time(NULL) - t;
		ft_printf("Frame drawn in %d seconds\n", t);
	}
}
