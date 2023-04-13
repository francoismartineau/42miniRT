/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:19:25 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 15:34:21 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "obj.h"
#include "def.h"

t_plane	*parse_plane(char const *line, int *err)
{
	t_plane	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	memcopy(res->coord,
		parse_vec(&line, err, any), 3 * sizeof(*res->coord));
	memcopy(res->ori,
		parse_vec(&line, err, signed_normalized), 3 * sizeof(*res->ori));
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_cylinder	*parse_cylinder(char const *line, int *err)
{
	t_cylinder	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	memcopy(res->coord,
		parse_vec(&line, err, any), 3 * sizeof(*res->coord));
	res->axis = parse_double(&line, err, signed_normalized);
	res->diam = parse_double(&line, err, positive);
	res->height = parse_double(&line, err, positive);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}
