/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranges.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:55:05 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 08:02:33 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	in_fov_range(unsigned int n)
{
	return (n <= 180);
}

int	positive_normalized(FPR n)
{
	return (n >= 0 && n <= 1);
}

int	signed_normalized(FPR n)
{
	return (n >= -1 && n <= 1);
}

int	positive(FPR n)
{
	return (n >= 0);
}

int	any(FPR n)
{
	(void) n;
	return (1);
}
