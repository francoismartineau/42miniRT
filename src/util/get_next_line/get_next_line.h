/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:56:49 by root              #+#    #+#             */
/*   Updated: 2023/05/30 16:35:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "util/util.h"

void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	get_buff_mem_size(size_t req_size);
char	*append_buff(char *buf, char *add);

#endif
