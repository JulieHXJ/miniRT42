/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/04/30 16:56:33 by dchrysov         ###   ########.fr       */
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

typedef struct s_gc_object
{
	void				*ptr;
	bool				marked;
	struct s_gc_object	*next;
}						t_gc_object;

/**
 * @note ratio range: [0.0, 1.0]
 * @note RGB range: [0, 255]
 */
typedef struct s_amb_light
{
	char	*id;
	double	ratio;
	int		rgb[3];
}			t_amb_light;

/**
 * @note orient range: [-1.0, 1.0]
 * @note fov range: [0, 180]
 */
typedef struct s_camera
{
	char	*id;
	double	viewpoint[3];
	double	orient[3];
	int		fov;
}			t_camera;

/**
 * @note brightness range: [0.0, 1.0]
 */
typedef struct s_light
{
	char	*id;
	double	coord[3];
	double	brightness;
}			t_light;

/**
 * @note rgb range: [0, 255]
 */
typedef struct s_sphere
{
	char	*id;
	double	center[3];
	double	diam;
	int		rgb[3];
}			t_sphere;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_plane
{
	char	*id;
	double	coord[3];
	double	normal[3];
	int		rgb[3];
}			t_plane;

/**
 * @note normal range: [-1.0, 1.0]
 * @note rgb range: [0, 255]
 */
typedef struct s_cylinder
{
	char	*id;
	double	center[3];
	double	normal[3];
	double	diam;
	double	height;
	int		rgb[3];
}			t_cylinder;

// Utils
void	free_array(char ***arr);
size_t	array_size(char **arr);
void	print_error(char *str, t_gc_object *gc_list);

// Parser
bool	invalid_file(char *fname, int fd);

// GC
void	*gc_alloc(size_t size, t_gc_object *gc_list);
void	gc_mark(void *ptr, t_gc_object *gc_list);
void	gc_sweep(t_gc_object *gc_list);

#endif