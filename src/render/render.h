/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:24 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/05/08 11:13:32 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "render/context.h"

typedef struct s_region
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	width;
	unsigned int	height;
}	t_region;

void	renderregion(t_context *context, const t_region region);
void	render(t_context *context);

#endif
