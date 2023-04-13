/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:25:23 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 08:56:07 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_OBJ_H
# define PARSE_OBJ_H

# include "obj.h"

typedef t_obj	*(*t_obj_parser)(char const *, int *);

t_obj	*parse_a_light(char const *line, int *err);
t_obj	*parse_camera(char const *line, int *err);
t_obj	*parse_light(char const *line, int *err);
t_obj	*parse_sphere(char const *line, int *err);
t_obj	*parse_plane(char const *line, int *err);
t_obj	*parse_cylinder(char const *line, int *err);
void	free_objs(t_obj **objs);

#endif
