/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:30:10 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 13:32:28 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <printf.h>
#include "obj.h"
#include "def.h"
#include "util/util.h"
#include "parse/parse.h"

#define FILE1 "rt/test1.rt"
#define STR1 "A	0.2										255,255,255\n\
C 	-50,0,20		0,0,0		70\n\
L	-40,0,30		0.7						255,255,255\n\
pl	0,0,0			0,1.0,0					255,0,225\n\
sp	0,0,20						20			255,0,0\n\
cy	50.0,0.0,20.6	0,0,1.0		14.2 21.42	10,0,255\n\
"

void	assert(char const *str, int res)
{
	if (!res)
	{
		write(STDERR_FILENO, str, strln(str));
		exit(EXIT_FAILURE);
	}
}

static int	eq_double(double a, double b)
{
	return (a >= b - .1 && a <= b + .1);
}

void	debug(void)
{
	int		fd;
	t_obj	**objs;

	fd = open(FILE1, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == ERROR)
		return ;
	write(fd, STR1, strln(STR1));
	close(fd);
	objs = parse_file(FILE1);
	assert("A", objs[0]->type == e_a_light);
	assert("0.2", eq_double(objs[0]->ratio, 0.2));
	assert("255,255,255", objs[0]->color == -1);
}
