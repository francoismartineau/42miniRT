/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:57 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 10:04:18 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "obj.h"
#include "def.h"

t_obj	*parse_a_light(char const *line, int *err)
{
	t_obj	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->type = e_a_light;
	res->ratio = parse_double(&line, err, positive_normalized);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_obj	*parse_camera(char const *line, int *err)
{
	t_obj	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->type = e_camera;
	parse_vec(res->coord, &line, err, any);
	parse_vec(res->ori, &line, err, signed_normalized);
	res->fov = parse_uint(&line, err, in_fov_range);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_obj	*parse_light(char const *line, int *err)
{
	t_obj		*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->type = e_light;
	parse_vec(res->coord, &line, err, any);
	res->ratio = parse_double(&line, err, positive_normalized);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_obj	*parse_sphere(char const *line, int *err)
{
	t_obj		*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->type = e_sphere;
	parse_vec(res->coord, &line, err, any);
	res->diam = parse_double(&line, err, positive);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}
