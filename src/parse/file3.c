/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:38:09 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 15:07:32 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "util/util.h"
#include "parse/parse.h"

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
