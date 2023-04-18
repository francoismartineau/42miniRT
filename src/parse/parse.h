/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:56:11 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 08:08:58 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "parse_obj.h"
# include "def.h"

t_obj			*parse_line(char *line, int *err);
t_obj			**parse_file(char const *path);
int				parse_color(char const **str, int *err);
FPR				parse_double(char const **str, int *err, int in_range(FPR));
void			parse_vec(FPR dst[3], char const **str,
					int *err, int in_range(FPR));
unsigned int	parse_uint(char const **str, int *err,
					int in_range(unsigned int));
void			skip_spaces(char const **str);

#endif
