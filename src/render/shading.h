/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 07:54:54 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/05/03 16:46:14 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

# include "obj.h"
# include "context.h"
# include "raycast.h"

t_vec3	shade(const t_obj *obj, const t_vec3 hit, const t_scene *s);

#endif
