/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:29:18 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 15:04:44 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "def.h"
#include "util/util.h"

void	skip_spaces(char const **str)
{
	while (**str <= ' ')
		++(*str);
}

static int	parse_color_channel(char const **str, int *err)
{
	int	res;

	if (!is_digit(**str))
		*err = ERROR;
	if (*err == ERROR)
		return (0);
	res = 0;
	while (is_digit(**str) && res <= 255)
	{
		res *= 10;
		res += *(*str)++ - '0';
	}
	if (res > 255)
		*err = ERROR;
	return (res);
}

int	parse_color(char const **str, int *err)
{
	int	i;
	int	res;
	int	chan;

	if (*err == ERROR)
		return (0);
	skip_spaces(str);
	i = 0;
	res = 0;
	while (i < 3)
	{
		chan = parse_color_channel(str, err);
		if (i < 2 && **str != ',')
			*err = ERROR;
		if (*err == ERROR)
			return (0);
		*str += **str == ',';
		res = (res << 8) + chan;
		++i;
	}
	return ((res << 8) | 0xFF);
}

FPR	parse_double(char const **str, int *err, int in_range(FPR))
{
	FPR	res;

	skip_spaces(str);
	if ((**str == '-' && !is_digit((*str)[1]))
		|| (**str != '-' && !is_digit(**str)))
		*err = ERROR;
	if (*err == ERROR)
		return (0);
	res = atod(str);
	if (!in_range(res))
	{
		*err = ERROR;
		return (0);
	}
	return (res);
}

void	parse_vec(FPR dst[3], char const **str,
	int *err, int in_range(FPR))
{
	int		i;

	if (*err == ERROR)
		return ;
	skip_spaces(str);
	i = 0;
	while (i < 3)
	{
		dst[i] = parse_double(str, err, in_range);
		if (i < 2 && **str != ',')
			*err = ERROR;
		if (*err == ERROR)
			return ;
		*str += (i < 2);
		++i;
	}
}
