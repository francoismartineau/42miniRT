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


// ratio: 0,1
typedef struct s_a_light
{
	double	ratio;
	int		color;
}	t_a_light;

typedef struct s_camera
{
	double			coord[3];
	double			ori[3];
	unsigned int	fov;
}	t_camera;

// ratio: 0,1
typedef struct s_light
{
	double			coord[3];
	double			ratio;
	int				color;
}	t_light;

typedef struct s_sphere
{
	double			coord[3];
	double			diam;
	int				color;
}	t_sphere;

// ori: -1,1
typedef struct s_plane
{
	double			coord[3];
	double			ori[3];
	int				color;
}	t_plane;

// coord: cylinder's center
// axis: -1,1
typedef struct s_cylinder
{
	double			coord[3];
	double			axis[3];
	double			diam;
	double			height;
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
	double			coord[3];
	double			ori[3];
	double			ratio;
	double			axis[3];
	double			diam;
	double			height;
	int				color;
	unsigned int	fov;
}	t_obj;

int	in_fov_range(unsigned int n);
int	positive_normalized(double n);
int	signed_normalized(double n);
int	any(double n);
int	positive(double n);

#endif
