/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/05/09 16:42:56 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

# include "mrt_color.h"
# include "mrt_vec3.h"
# include "../lib/libft/inc/libft.h"
# include "../lib/getnextline/inc/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

/* ************************************************************************** */
/* ENUMS & DEFINES                                                            */
/* ************************************************************************** */

# define USAGE_MSG "Usage: ./minirt scenes/<file_name>.rt"
# define RED "\033[31m"
# define RST "\033[0m"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	//Cone, Hyperboloid, Paraboloid

	// CAMERA,//i thingk its not necessary to put these types cuz there is only ono cam and one ambient right?
	// AMB_LIGHT
}	t_obj_type;


/* ************************************************************************** */
/* CORE MATH STRUCTURES                                                       */
/* ************************************************************************** */

//implyment vectors for center, normal and point on plane
typedef struct s_vec3	t_vec3;
typedef struct s_color	t_color;


/* ************************************************************************** */
/* MEMORY GARBAGE COLLECTOR OBJECT                                            */
/* ************************************************************************** */

typedef struct s_gc_object
{
	void				*ptr;
	bool				marked;
	struct s_gc_object	*next;
}						t_gc_object;


/* ************************************************************************** */
/* OBJECTS                                                                    */
/* ************************************************************************** */
/**
 * @note rgb range: [0, 255]
 */
typedef struct s_sphere
{
	// t_obj_type	type;//i think its not necessary to put type here, cuz we have it we creating object
	char		*id;
	double		diam;
	// int				rgb[3];
	// double			center[3];//instead i use vertor
	t_vec3		center;
	t_color		color;
}				t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	// t_obj_type	type;
	char		*id;//what is the purpose of this
	// double		normal[3];
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
}				t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	// t_obj_type	type;
	char		*id;//what for
	// double		normal[3];
	double		diam;
	double		height;
	t_vec3		center;
	t_vec3		normal;
	t_color		color;
}				t_cylinder;

/**
 * @note ratio range: [0.0, 1.0]
 * @note RGB range: [0, 255]
 */
typedef struct s_amb_light
{
	// t_obj_type	type;//unnecessary i think
	double		ratio;
	// int			rgb[3];
	t_color		color;
}				t_amb_light;

/**
 * @note orient range: [-1.0, 1.0]
 * @note fov range: [0, 180]
 */
typedef struct s_camera
{
	// t_obj_type	type;
	// double		viewpoint[3];
	// double		orient[3];
	t_vec3		viewpoint;
	t_vec3		orientation;
	int			fov;// field of view, nor
}				t_camera;

/**
 * @note brightness range: [0.0, 1.0]
 */
//i think its better to use linked list cuz we will have more lights later
typedef struct s_light
{
	// t_obj_type	type;
	double		coord[3];
	double		brightness;
	t_vec3		position;
	t_color		color;
}				t_light;



/* ************************************************************************** */
/* GENERIC OBJECT WRAPPER                                                     */
/* ************************************************************************** */

//i put color and center into certain object's structure so can be used direct when calling the object
typedef struct s_object
{
	t_obj_type		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}	u_type;
	// int				rgb[3];
	// double			center[3];
	void		*content;//added
	struct s_object	*next;
	struct s_object	*previous;
}	t_object;

/* ************************************************************************** */
/* SCENE STRUCTURE                                                            */
/* ************************************************************************** */

typedef struct s_scene
{
	t_amb_light	*amb_light;
	t_camera	*cam;
	t_light		*light;// make it a list
	t_object	*obj;
}				t_scene;

typedef struct s_minirt
{
	mlx_t		*mlx;
	// void		*window;
	t_scene		*scene;
} t_minirt;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES                                                        */
/* ************************************************************************** */

// Utils
void	free_array(char ***arr);
size_t	array_size(char **arr);
void	print_error(char *str, t_gc_object *gc_list);
double	ft_atod(const char *str);

//Check
bool	valid_file(int ac, char **av);

//Init
void	*scene_init(t_scene *scene);


// Parser
void	parser(char *fname, t_scene **scene);
void	create_environment(char *line, t_scene **scene);
void	create_objects(char *line, t_scene **scene);
//void create_light();
void	rgb_range_check(t_object **obj, char *rgb);
void	normal_vector_range_check(t_object **obj, t_obj_type type, char *vec);
void	center_point_assign(t_object **obj, char *point);

// GC
void	*gc_alloc(size_t size, t_gc_object *gc_list);
void	gc_mark(void *ptr, t_gc_object *gc_list);
void	gc_free(t_gc_object *gc_list);

#endif
