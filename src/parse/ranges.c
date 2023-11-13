/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranges.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:55:05 by francoma          #+#    #+#             */
/*   Updated: 2023/11/09 16:19:40 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	in_fov_range(unsigned int n)
{
	return (n <= 180);
}

int	positive_normalized(float n)
{
	return (n >= 0 && n <= 1);
}

int	signed_normalized(float n)
{
	return (n >= -1 && n <= 1);
}

int	positive(float n)
{
	return (n >= 0);
}

int	any(float n)
{
	(void) n;
	return (1);
}
