/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:57 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 15:33:47 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "obj.h"
#include "def.h"

t_a_light	*parse_a_light(char const *line, int *err)
{
	t_a_light	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->ratio = parse_double(&line, err, positive_normalized);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_camera	*parse_camera(char const *line, int *err)
{
	t_camera	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	memcopy(res->coord,
		parse_vec(&line, err, any), 3 * sizeof(*res->coord));
	memcopy(res->ori,
		parse_vec(&line, err, signed_normalized), 3 * sizeof(*res->ori));
	res->fov = parse_uint(&line, err, in_fov_range);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_light	*parse_light(char const *line, int *err)
{
	t_light		*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	memcopy(res->coord,
		parse_vec(&line, err, any), 3 * sizeof(*res->coord));
	res->ratio = parse_double(&line, err, positive_normalized);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_sphere	*parse_sphere(char const *line, int *err)
{
	t_sphere		*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	memcopy(res->coord,
		parse_vec(&line, err, any), 3 * sizeof(*res->coord));
	res->diam = parse_double(&line, err, positive);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}
