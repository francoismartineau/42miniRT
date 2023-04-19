/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:29:18 by francoma          #+#    #+#             */
/*   Updated: 2023/04/19 08:32:16 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "def.h"
#include "parse.h"
#include "util/util.h"

void	parse_color(FPR dst[3], char const **str, int *err)
{
	parse_vec(dst, str, err, is_uchar);
	dst[0] /=255;
	dst[1] /=255;
	dst[2] /=255;
}

FPR	parse_double(char const **str, int *err, int in_range(FPR))
{
	FPR	res;

	skip_spaces(str);
	if ((**str == '-' && !is_digit((*str)[1]))
		|| (**str != '-' && !is_digit(**str) && **str != '.'))
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

unsigned int	parse_uint(char const **str, int *err,
	int in_range(unsigned int))
{
	unsigned int	res;

	skip_spaces(str);
	if (!is_digit(**str))
		*err = ERROR;
	if (*err == ERROR)
		return (0);
	res = 0;
	while (is_digit(**str) && in_range(res))
		res = (res * 10) + *(*str)++ - '0';
	if (!in_range(res))
		*err = ERROR;
	return (res);
}
