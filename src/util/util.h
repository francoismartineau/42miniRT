/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:27:11 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 08:47:44 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stddef.h>

#include "def.h"

size_t	strln(char const *str);
char	*strchar(const char *s, int c);
int		strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);

FPR		atod(char const **str);
int		is_digit(char c);

void	*ft_malloc(size_t size);
void	*ft_free(void **m);
void	*memcopy(void *dst, const void *src, size_t n);
void	ft_memset(void *b, int c, size_t len);

#endif
