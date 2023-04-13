/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:35:13 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 07:43:16 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	strln(char const *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		++len;
	return (len);
}

char	*strchar(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	return (NULL);
}

int	strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	diff = 0;
	i = 0;
	while (diff == 0 && (s1[i] || s2[i]) && i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (diff);
}
