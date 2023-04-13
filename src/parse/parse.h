/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:56:11 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 10:03:06 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "parse_obj.h"

t_obj			**parse_file(char const *path);
int				parse_color(char const **str, int *err);
double			parse_double(char const **str, int *err, int in_range(double));
void			parse_vec(double dst[3], char const **str,
					int *err, int in_range(double));
unsigned int	parse_uint(char const **str, int *err,
					int in_range(unsigned int));
void			skip_spaces(char const **str);

#endif
