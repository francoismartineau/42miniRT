/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:54:46 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 10:55:13 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# define ID_A_LIGHT "A"
# define ID_CAMERA "C"
# define ID_LIGHT "L"
# define ID_SPHERE "sp"
# define ID_PLANE "pl"
# define ID_CYLINDER "cy"
# define OBJ_QTY 6

# include "def.h"

# include "util/vec3.h"

// ratio: 0,1
typedef struct s_a_light
{
	FPR		ratio;
	int		color;
}	t_a_light;

typedef struct s_camera
{
	t_vec3			pos;
	FPR				ori[3];
	unsigned int	fov;
}	t_camera;

// ratio: 0,1
typedef struct s_light
{
	t_vec3			pos;
	FPR				ratio;
	int				color;
}	t_light;

typedef struct s_sphere
{
	t_vec3			pos;
	FPR				rad;
	int				color;
	t_vec3			colorv;
}	t_sphere;

// ori: -1,1
typedef struct s_plane
{
	t_vec3			pos;
	FPR				ori[3];
	int				color;
}	t_plane;

// coord: cylinder's center
// axis: -1,1
typedef struct s_cylinder
{
	t_vec3			pos;
	FPR				axis[3];
	FPR				rad;
	FPR				height;
	int				color;
}	t_cylinder;

typedef enum e_type
{
	e_a_light,
	e_camera,
	e_light,
	e_sphere,
	e_plane,
	e_cylinder,
}	t_type;

typedef struct s_obj
{
	t_type			type;
	union
	{
		t_cylinder	cylinder;
		t_plane		plane;
		t_sphere	sphere;
		t_light		light;
		t_camera	camera;
		t_a_light	a_light;
	};
}	t_obj;

int	in_fov_range(unsigned int n);
int	positive_normalized(FPR n);
int	signed_normalized(FPR n);
int	any(FPR n);
int	positive(FPR n);

#endif
