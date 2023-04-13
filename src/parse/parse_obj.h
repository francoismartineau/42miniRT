/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:25:23 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 14:28:20 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_OBJ_H
# define PARSE_OBJ_H

# include "obj.h"

t_a_light	*parse_a_light(char const *line, int *err);
t_camera	*parse_camera(char const *line, int *err);
t_light		*parse_light(char const *line, int *err);
t_sphere	*parse_sphere(char const *line, int *err);
t_plane		*parse_plane(char const *line, int *err);
t_cylinder	*parse_cylinder(char const *line, int *err);

#endif
