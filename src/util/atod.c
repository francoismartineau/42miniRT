/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:26:56 by francoma          #+#    #+#             */
/*   Updated: 2023/11/09 16:20:24 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "def.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static long	extract_integral(char const **str)
{
	long	integral;	

	integral = 0;
	while (is_digit(**str))
	{
		integral *= 10;
		integral += *(*str)++ - '0';
	}
	return (integral);
}

static float	extract_fractional(char const **str)
{
	long			fract;
	unsigned int	fract_len;

	fract = 0;
	fract_len = 0;
	while (is_digit(**str))
	{
		fract *= 10;
		fract += *(*str)++ - '0';
		++fract_len;
	}
	if (!fract_len)
		return (0);
	return ((float)fract / powf(10, fract_len));
}

float	atod(char const **str)
{
	int		sign;
	float	integral;	

	while (**str <= ' ')
		++(*str);
	sign = (**str == '-') * -2 + 1;
	*str += (**str == '-');
	if (**str != '.')
		integral = extract_integral(str);
	else
		integral = 0;
	if (**str != '.')
		return (sign * integral);
	++*str;
	return (sign * (integral + extract_fractional(str)));
}
