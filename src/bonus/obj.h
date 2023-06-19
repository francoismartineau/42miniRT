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
# include "math/mat3.h"
# include "util/vec3.h"

// ratio: 0,1
typedef struct s_a_light
{
	t_vec3	color;
}	t_a_light;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			ori;
	t_mat3			rot;
	FPR				fov;
}	t_camera;

// ratio: 0,1
typedef struct s_light
{
	t_vec3			pos;
	t_vec3			color;
}	t_light;

typedef struct s_sphere
{
	t_vec3			pos;
	t_vec3			color;
	t_vec3			emit;
	FPR				r;
	FPR				rad;
}	t_sphere;

// ori: -1,1
typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			color;
	t_vec3			emit;
	FPR				r;
	t_vec3			ori;
}	t_plane;

// coord: cylinder's center
// axis: -1,1
typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			color;
	t_vec3			emit;
	FPR				r;
	t_vec3			axis;
	FPR				rad;
	FPR				height;
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
		struct
		{
			t_vec3	pos;
			t_vec3	color;
			t_vec3	emit;
			FPR		r;
		};
	};
}	t_obj;

typedef struct s_scene
{
	t_light		*lights;
	size_t		lightc;
	t_obj		*objs;
	size_t		objc;
	t_a_light	a_light;
	t_camera	camera;
}	t_scene;

#endif
