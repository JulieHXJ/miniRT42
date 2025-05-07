/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/05/07 11:56:19 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

# include "../lib/libft/inc/libft.h"
# include "../lib/getnextline/inc/get_next_line.h"

# define USAGE_MSG "Usage: ./minirt scenes/<file_name>.rt"
# define RED "\033[31m"
# define RST "\033[0m"

typedef struct s_gc_object
{
	void				*ptr;
	bool				marked;
	struct s_gc_object	*next;
}						t_gc_object;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	CAMERA,
	AMB_LIGHT
}	t_obj_type;

/**
 * @note ratio range: [0.0, 1.0]
 * @note RGB range: [0, 255]
 */
typedef struct s_amb_light
{
	t_obj_type	type;
	double		ratio;
	int			rgb[3];
}				t_amb_light;

/**
 * @note orient range: [-1.0, 1.0]
 * @note fov range: [0, 180]
 */
typedef struct s_camera
{
	t_obj_type	type;
	double		viewpoint[3];
	double		orient[3];
	int			fov;
}				t_camera;

/**
 * @note brightness range: [0.0, 1.0]
 */
typedef struct s_light
{
	t_obj_type	type;
	double		coord[3];
	double		brightness;
}				t_light;

/**
 * @note rgb range: [0, 255]
 */
typedef struct s_sphere
{
	t_obj_type	type;
	char		*id;
	double		diam;
}				t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	t_obj_type	type;
	char		*id;
	double		normal[3];
}				t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	t_obj_type	type;
	char		*id;
	double		normal[3];
	double		diam;
	double		height;
}				t_cylinder;

/**
 * @brief Generic declation of the geometrical objects
 */
typedef struct s_object
{
	t_obj_type		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}	u_type;
	int				rgb[3];
	double			center[3];
	struct s_object	*next;
	struct s_object	*previous;
}	t_object;

typedef struct s_scene
{
	t_amb_light	*amb_light;
	t_camera	*cam;
	t_light		*light;
	t_object	*obj;
}				t_scene;

// Utils
void	free_array(char ***arr);
size_t	array_size(char **arr);
void	print_error(char *msg, t_gc_object **gc_list);
double	ft_atod(const char *str);

// Parser
bool	invalid_file(int ac, char **av);
t_scene	*scene_init(t_gc_object **list);
void	parser(char *fname, t_scene **scene, t_gc_object **gc_list);
void	create_environment(char *line, t_scene **scene, t_gc_object **gc_list);
void	create_objects(char *line, t_scene **scene, t_gc_object **gc_list);
void	rgb_range_check(t_object **obj, char *rgb, t_gc_object **gc_list);
void	normal_vector_range_check(t_object **obj, char *vec, t_gc_object **lis);
void	center_point_assign(t_object **obj, char *point);

// GC
void	*gc_alloc(size_t size, t_gc_object **gc_list);
void	gc_mark(void *ptr, t_gc_object *gc_list);
void	gc_sweep(t_gc_object **gc_list);


void	print_obj(t_scene scene);

#endif
