/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:24 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/16 13:35:22 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "render/context.h"

#define SAMPLE_COUNT 256
#define SAMPLE_DEPTH 8

typedef struct s_region
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	width;
	unsigned int	height;
	unsigned int	imgid;
}	t_region;

void	renderregion(t_context *context, const t_region region);
void	render(t_context *context);

#endif
