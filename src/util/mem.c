/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:46 by francoma          #+#    #+#             */
/*   Updated: 2023/04/19 14:51:10 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "exit.h"

void	*ft_malloc(size_t size)
{
	static int	i = 0;
	void		*res;

	res = malloc(size);
	fprintf(stderr, "malloc: %02i %p\n", ++i, res);
	if (!res)
		exit_error("malloc failure");
	return (res);
}

void	*ft_free(void **m)
{
	free(*m);
	fprintf(stderr, "free: %p\n", *m);
	*m = NULL;
	return (*m);
}

void	*memcopy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void	ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
}
