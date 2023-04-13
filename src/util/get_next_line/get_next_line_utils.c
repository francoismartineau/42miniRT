/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:56:38 by root              #+#    #+#             */
/*   Updated: 2023/04/13 07:43:01 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst || !src)
		return (NULL);
	if (dst == src)
		return (dst);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			((unsigned char *) dst)[i - 1] = ((unsigned char *) src)[i - 1];
			i--;
		}
	}
	return (dst);
}

size_t	get_buff_mem_size(size_t req_size)
{
	size_t	size;

	size = 128;
	while (size < req_size)
		size *= 2;
	return (size);
}

char	*append_buff(char *buf, char *add)
{
	char	*res;
	size_t	buf_l;
	size_t	add_l;
	size_t	m_size;

	buf_l = strln(buf);
	add_l = strln(add);
	m_size = get_buff_mem_size(buf_l + add_l + 1);
	if (!buf || m_size != get_buff_mem_size(buf_l + 1))
	{
		res = malloc(sizeof(*res) * (m_size));
		if (!res)
		{
			free(buf);
			return (NULL);
		}
		ft_memmove(res, buf, buf_l);
		free(buf);
	}
	else
		res = buf;
	ft_memmove(res + buf_l, add, add_l);
	res[buf_l + add_l] = '\0';
	return (res);
}
