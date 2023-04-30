/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:29:18 by francoma          #+#    #+#             */
/*   Updated: 2023/04/29 20:30:04 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "def.h"
#include "parse.h"
#include "util/util.h"

static void	parsing_error(char const *str, int *err)
{
	char	*line_n;
	size_t	char_n;
	size_t	i;

	*err = ERROR;
	write(STDERR_FILENO, NAME, strln(NAME));
	write(STDERR_FILENO, ": parsing error: at line ", 25);
	line_n = intoa(get_parsing_data()->line_n);
	write(STDERR_FILENO, line_n, strln(line_n));
	ft_free((void **) &line_n);
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, get_parsing_data()->line,
		strln(get_parsing_data()->line));
	char_n = str - get_parsing_data()->line;
	i = -1;
	while (++i < char_n)
		if (get_parsing_data()->line[i] == '\t')
			write(STDERR_FILENO, "\t", 1);
	else
		write(STDERR_FILENO, " ", 1);
	write(STDERR_FILENO, "^\n", 2);
}

void	parse_color(FPR dst[3], char const **str, int *err)
{
	if (*err == ERROR)
		return ;
	parse_vec(dst, str, err, is_uchar);
	dst[0] /= 255;
	dst[1] /= 255;
	dst[2] /= 255;
}

FPR	parse_double(char const **str, int *err, int in_range(FPR))
{
	FPR	res;

	if (*err == ERROR)
		return (0);
	skip_spaces(str);
	if ((**str == '-' && !is_digit((*str)[1]) && (*str)[1] != '.')
		|| (**str != '-' && !is_digit(**str) && **str != '.'))
		parsing_error(*str, err);
	if (*err == ERROR)
		return (0);
	res = atod(str);
	if (!in_range(res))
	{
		parsing_error(*str, err);
		return (0);
	}
	return (res);
}

void	parse_vec(FPR dst[3], char const **str,
	int *err, int in_range(FPR))
{
	int		i;

	if (*err == ERROR)
		return ;
	skip_spaces(str);
	i = 0;
	while (i < 3)
	{
		dst[i] = parse_double(str, err, in_range);
		if (i < 2 && **str != ',' && *err != ERROR)
			parsing_error(*str, err);
		if (*err == ERROR)
			return ;
		*str += (i < 2);
		++i;
	}
}

unsigned int	parse_uint(char const **str, int *err,
	int in_range(unsigned int))
{
	unsigned int	res;

	if (*err == ERROR)
		return (0);
	skip_spaces(str);
	if (!is_digit(**str))
		parsing_error(*str, err);
	if (*err == ERROR)
		return (0);
	res = 0;
	while (is_digit(**str) && in_range(res))
		res = (res * 10) + *(*str)++ - '0';
	if (!in_range(res))
		parsing_error(*str, err);
	return (res);
}
