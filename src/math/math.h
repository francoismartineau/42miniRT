/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:23:36 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 08:51:59 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "def.h"

FPR				clamp(FPR value, FPR min, FPR max);
int				imin(int a, int b);
int				imax(int a, int b);
unsigned int	umin(unsigned int a, unsigned int b);
unsigned int	umax(unsigned int a, unsigned int b);

#endif
