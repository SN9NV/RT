/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <angusdippenaar@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 12:30:08 by adippena          #+#    #+#             */
/*   Updated: 2016/08/29 20:56:20 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_light_values(t_env *e, char *pt1, char *pt2)
{
	t_split_string	values;

	values = ft_nstrsplit(pt2, ' ');
	if (!ft_strcmp(pt1, "LOC"))
		e->light[e->lights]->loc = get_vector(e, values);
	else if (!ft_strcmp(pt1, "COLOUR"))
		e->light[e->lights]->colour = get_colour(e, values);
	else if (!ft_strcmp(pt1, "INTENSITY"))
		e->light[e->lights]->lm = ft_atod(values.strings[0]) * 3.415;
	else if (!ft_strcmp(pt1, "HALF"))
		e->light[e->lights]->half = ft_atod(values.strings[0]);
	ft_free_split(&values);
}

static void	init_light(t_light *l)
{
	l->loc = (t_vector){0.0, 0.0, 5.0};
	l->colour = (t_colour){1.0, 1.0, 1.0, 1.0};
	l->lm = 3.415;
	l->half = 0.0;
}

void		get_light_attributes(t_env *e, int fd)
{
	t_split_string	attr;
	char			*temp_line;

	attr.words = 0;
	e->light[e->lights] = (t_light *)malloc(sizeof(t_light));
	init_light(e->light[e->lights]);
	while (ft_gnl(fd, &temp_line))
	{
		if (temp_line[0] == '\0')
			break ;
		attr = ft_nstrsplit(temp_line, '\t');
		ft_strdel(&temp_line);
		if (attr.words < 2)
			err(FILE_FORMAT_ERROR, "get_light_attributes", e);
		set_light_values(e, attr.strings[0], attr.strings[1]);
		ft_free_split(&attr);
	}
	ft_strdel(&temp_line);
	++e->lights;
}
