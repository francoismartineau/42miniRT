/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:56:11 by francoma          #+#    #+#             */
/*   Updated: 2023/11/09 16:23:46 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "obj.h"
# include "def.h"

int				parse_file(char const *path, t_scene *scene);

typedef void	(*t_obj_parser)(char const *, int *, t_scene *);

void			parse_a_light(char const *line, int *err, t_scene *scene);
void			parse_camera(char const *line, int *err, t_scene *scene);
void			parse_light(char const *line, int *err, t_scene *scene);
void			parse_sphere(char const *line, int *err, t_scene *scene);
void			parse_plane(char const *line, int *err, t_scene *scene);
void			parse_cylinder(char const *line, int *err, t_scene *scene);

void			parse_color(float dst[3], char const **str, int *err);
float			parse_double(char const **str, int *err, int in_range(float));
void			parse_vec(float dst[3], char const **str,
					int *err, int in_range(float));
unsigned int	parse_uint(char const **str, int *err,
					int in_range(unsigned int));

int				in_fov_range(unsigned int n);
int				positive_normalized(float n);
int				signed_normalized(float n);
int				any(float n);
int				positive(float n);
int				is_uchar(float n);

void			append_obj(t_scene *scene, t_obj *new_alloc);
void			free_scene(t_scene *scene);

typedef struct s_parsing_data
{
	size_t	line_n;
	char	*line;
}	t_parsing_data;
t_parsing_data	*get_parsing_data(void);

#endif
