/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:16:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/05/07 11:39:15 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

size_t	array_size(char **arr)
{
	size_t	size;

	size = 0;
	while (*arr)
	{
		size++;
		arr++;
	}
	return (size);
}

void	free_array(char ***arr)
{
	size_t	i;
	size_t	size;

	if (!arr || !*arr)
		return ;
	size = array_size(*arr);
	i = -1;
	while (++i < size)
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	print_error(char *msg, t_gc_object **gc_list)
{
	printf("%sError%s: %s\n", RED, RST, msg);
	if (gc_list)
		gc_sweep(gc_list);
	exit(1);
}

/**
 * @brief Convert string to double
 * @param str String to convert (format: [-+]?[0-9]*\.?[0-9]+)
 * @return Double value
 */
double	ft_atod(const char *s)
{
	double	res;
	double	frac;
	double	div;
	int		sign;

	sign = 1;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	res = 0;
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	frac = 0;
	div = 10;
	if (*s == '.')
	{
		s++;
		while (*s >= '0' && *s <= '9')
		{
			frac += (*s++ - '0') / div;
			div *= 10;
		}
	}
	return (sign * (res + frac));
}

void	print_obj(t_scene scene)
{
	printf("\n");
	printf("AMB_LIGHT\n");
	printf("%.1f ", scene.amb_light->ratio);
	printf("%d,%d,%d\n", scene.amb_light->rgb[0], scene.amb_light->rgb[1], scene.amb_light->rgb[2]);
	printf("\n");
	printf("CAMERA\n");
	printf("%.1f,%.1f,%.1f ", scene.cam->viewpoint[0], scene.cam->viewpoint[1], scene.cam->viewpoint[2]);
	printf("%.1f,%.1f,%.1f ", scene.cam->orient[0], scene.cam->orient[1], scene.cam->orient[2]);
	printf("%d\n", scene.cam->fov);
	printf("\n");
	printf("LIGHT\n");
	printf("%.1f,%.1f,%.1f ", scene.light->coord[0], scene.light->coord[1], scene.light->coord[2]);
	printf("%.1f\n", scene.light->brightness);
	printf("\n");
	while (scene.obj)
	{
		if (scene.obj->type == PLANE)
		{
			printf("PLANE\n");
			printf("%.1f,%.1f,%.1f ", scene.obj->center[0], scene.obj->center[1], scene.obj->center[2]);
			printf("%.1f,%.1f,%.1f ", scene.obj->u_type.plane.normal[0], scene.obj->u_type.plane.normal[1], scene.obj->u_type.plane.normal[2]);
			printf("%d,%d,%d\n", scene.obj->rgb[0], scene.obj->rgb[1], scene.obj->rgb[2]);
			printf("\n");
		}
		else if (scene.obj->type == SPHERE)
		{
			printf("SPHERE\n");
			printf("%.1f,%.1f,%.1f ", scene.obj->center[0], scene.obj->center[1], scene.obj->center[2]);
			printf("%.1f ", scene.obj->u_type.sphere.diam);
			printf("%d,%d,%d\n", scene.obj->rgb[0], scene.obj->rgb[1], scene.obj->rgb[2]);
			printf("\n");
		}
		else
		{
			printf("CYLINDER\n");
			printf("%.1f,%.1f,%.1f ", scene.obj->center[0], scene.obj->center[1], scene.obj->center[2]);
			printf("%.1f,%.1f,%.1f ", scene.obj->u_type.plane.normal[0], scene.obj->u_type.plane.normal[1], scene.obj->u_type.plane.normal[2]);
			printf("%.1f ", scene.obj->u_type.cylinder.diam);
			printf("%.1f ", scene.obj->u_type.cylinder.height);
			printf("%d,%d,%d\n", scene.obj->rgb[0], scene.obj->rgb[1], scene.obj->rgb[2]);
			printf("\n");
		}
		scene.obj = scene.obj->next;
	}
	exit(0);
}
