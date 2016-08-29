/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <angusdippenaar@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 15:53:16 by adippena          #+#    #+#             */
/*   Updated: 2016/08/29 21:18:21 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	get_vector(t_env *e, t_split_string values)
{
	if (values.words != 3)
		err(FILE_FORMAT_ERROR, "get_vector", e);
	return ((t_vector){
		ft_atod(values.strings[0]),
		ft_atod(values.strings[1]),
		ft_atod(values.strings[2])});
}

t_vector	get_unit_vector(t_env *e, t_split_string values)
{
	if (values.words != 3)
		err(FILE_FORMAT_ERROR, "get_vector", e);
	return (vunit((t_vector){
		ft_atod(values.strings[0]),
		ft_atod(values.strings[1]),
		ft_atod(values.strings[2])}));
}
