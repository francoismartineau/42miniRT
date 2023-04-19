/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/04/19 15:10:08 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "render/context.h"
#include "render/raycast.h"
#include "math/vecmath.h"
#include "exit.h"
#include "shading.h"
#include "parse/parse.h"

#include <math.h>

void	loop(void *param)
{
	render(param);
}

int	main(int argc, char const *argv[])
{
	t_context	ctx;

	(void) argc;
	(void) argv;
	if (argc != 2)
		exit_error(MSG_ARG_ERR);
	context_new(&ctx, 800, 600);
	if (parse_file(argv[1], &ctx.scene) == ERROR)
		exit(EXIT_FAILURE);
		exit_error(MSG_PARSE_ERR);
	// mlx_loop_hook(ctx.mlx, loop, &ctx);
	// mlx_loop(ctx.mlx);
	context_free(&ctx);
	return (0);
}
