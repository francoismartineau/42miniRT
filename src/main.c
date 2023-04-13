/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 15:36:24 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parse/parse.h"
// #include "util/util.h"

int	main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;
	parse_file("file.rt");
	return (0);
}
