/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:29:18 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 14:21:16 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

double	parse_double(char const **str, int *err, int in_range(double))
{
	double	res;

	skip_spaces(str);
	if (!is_digit(**str))
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

double	*parse_vec(char const **str, int *err, int in_range(double))
{
	int		i;
	double	*res;

	if (*err == ERROR)
		return (NULL);
	skip_spaces(str);
	res = ft_malloc(3);
	i = 0;
	while (i < 3)
	{
		res[i] = parse_double(str, err, in_range);
		if (i < 2 && **str != ',')
			*err = ERROR;
		if (*err == ERROR)
			return (ft_free((void **) &res));
		++i;
	}
	return (res);
}
