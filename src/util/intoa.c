/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 10:53:37 by francoma          #+#    #+#             */
/*   Updated: 2023/04/19 11:05:32 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/util.h"

static unsigned char	intoa_strlen(long n)
{
	unsigned char	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	_intoa(long n, char **s_pos)
{
	if (n > 9)
		_intoa(n / 10, s_pos);
	**s_pos = n % 10 + '0';
	(*s_pos)++;
}

char	*intoa(int n)
{
	char			*s;
	char			*s_pos;
	long			l_n;

	l_n = n;
	s = ft_malloc(intoa_strlen(l_n) + 1);
	if (!s)
		return (NULL);
	s_pos = s;
	if (l_n < 0)
	{
		*s_pos++ = '-';
		l_n = -l_n;
	}
	_intoa(l_n, &s_pos);
	*s_pos = '\0';
	return (s);
}
