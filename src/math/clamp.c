/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:24:41 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 08:51:38 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

#include <math.h>

#include "util/vec3.h"

FPR	clamp(FPR x, FPR min, FPR max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned int	umin(unsigned int a, unsigned int b)
{
	if (a < b)
		return (a);
	return (b);
}

unsigned int	umax(unsigned int a, unsigned int b)
{
	if (a > b)
		return (a);
	return (b);
}
