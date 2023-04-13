/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:26:56 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 09:38:57 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static long	extract_integral(char const **str)
{
	long			integral;	

	integral = 0;
	while (is_digit(**str))
	{
		integral *= 10;
		integral += *(*str)++ - '0';
	}
	return (integral);
}

static double	extract_fractional(char const **str)
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
	return ((double)fract / (fract_len * 10));
}

double	atod(char const **str)
{
	int		sign;
	double	integral;	

	while (**str <= ' ')
		++(*str);
	sign = (**str == '-') * -2 + 1;
	*str += (**str == '-');
	integral = extract_integral(str);
	if (**str != '.')
		return (sign * integral);
	++*str;
	return (sign * (integral + extract_fractional(str)));
}
