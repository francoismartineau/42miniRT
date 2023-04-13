/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranges.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:55:05 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 13:38:26 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	in_fov_range(unsigned int n)
{
	return (n <= 180);
}

int	positive_normalized(double n)
{
	return (n >= 0 && n <= 1);
}

int	signed_normalized(double n)
{
	return (n >= -1 && n <= 1);
}

int	positive(double n)
{
	return (n >= 0);
}

int	any(double n)
{
	(void) n;
	return (1);
}
