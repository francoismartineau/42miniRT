/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:46 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 13:15:11 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "exit.h"

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		exit_error("malloc failure");
	return (res);
}

void	*ft_free(void **m)
{
	free(*m);
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
