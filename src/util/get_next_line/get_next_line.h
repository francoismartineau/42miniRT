/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:56:49 by root              #+#    #+#             */
/*   Updated: 2023/04/12 10:40:14 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "util/util.h"

void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	get_buff_mem_size(size_t req_size);
char	*append_buff(char *buf, char *add);

#endif
