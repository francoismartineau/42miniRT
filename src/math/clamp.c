/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:24:41 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/19 10:24:54 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

FPR	clamp(FPR x, FPR min, FPR max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}