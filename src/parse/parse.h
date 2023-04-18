/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:56:11 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 15:12:54 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "obj.h"
# include "def.h"

int				parse_file(char const *path, t_scene *scene);

typedef t_obj	*(*t_obj_parser)(char const *, int *, t_scene *);

void			parse_a_light(char const *line, int *err, t_scene *scene);
void			parse_camera(char const *line, int *err, t_scene *scene);
void			parse_light(char const *line, int *err, t_scene *scene);
void			parse_sphere(char const *line, int *err, t_scene *scene);
void			parse_plane(char const *line, int *err, t_scene *scene);
void			parse_cylinder(char const *line, int *err, t_scene *scene);

int				parse_color(char const **str, int *err);
FPR				parse_double(char const **str, int *err, int in_range(FPR));
void			parse_vec(FPR dst[3], char const **str,
					int *err, int in_range(FPR));
unsigned int	parse_uint(char const **str, int *err,
					int in_range(unsigned int));
void			skip_spaces(char const **str);

int				in_fov_range(unsigned int n);
int				positive_normalized(FPR n);
int				signed_normalized(FPR n);
int				any(FPR n);
int				positive(FPR n);
		
void			**append_scene(void **src, void *new, size_t size);
void			free_scene(t_scene *scene);

#endif
