/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/06 17:12:19 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	set_camera(t_scene **scene, char **tokens)
{
	char	**vp;
	char	**orient;
	double	d_orient[3];

	vp = ft_split(tokens[1], ',');
	orient = ft_split(tokens[2], ',');
	d_orient[0] = ft_atod(orient[0]);
	d_orient[1] = ft_atod(orient[1]);
	d_orient[2] = ft_atod(orient[2]);
	if (d_orient[0] <= -1.0 || d_orient[0] >= 1.0 || d_orient[1] <= -1.0
		|| d_orient[1] >= 1.0 || d_orient[2] <= -1.0 || d_orient[2] >= 1.0)
		return (print_error("Camera orient out of range [-1.0, 1.0]", NULL));
	if (ft_atoi(tokens[3]) < 0 || ft_atoi(tokens[3]) > 180)
		return (print_error("Camera FOV out of range [0, 180]", NULL));
	(*scene)->cam = malloc(sizeof(t_camera));
	if (!(*scene)->cam)
		return (print_error("Error allocating memory for camera", NULL));
	(*scene)->cam->viewpoint[0] = ft_atod(vp[0]);
	(*scene)->cam->viewpoint[1] = ft_atod(vp[1]);
	(*scene)->cam->viewpoint[2] = ft_atod(vp[2]);
	(*scene)->cam->orient[0] = d_orient[0];
	(*scene)->cam->orient[1] = d_orient[1];
	(*scene)->cam->orient[2] = d_orient[2];
	(*scene)->cam->fov = ft_atoi(tokens[3]);
	return (free_array(&vp), free_array(&orient));
}

static void	set_amb_light(t_scene **scene, char **tokens)
{
	char	**rgb;
	double	ratio;
	int		int_rgb[3];

	ratio = ft_atod(tokens[1]);
	if (ratio <= 0.0 || ratio >= 1.0)
		return (print_error("Ambient light ratio out of range [0.0, 1.0]",
				NULL));
	rgb = ft_split(tokens[2], ',');
	int_rgb[0] = ft_atoi(rgb[0]);
	int_rgb[1] = ft_atoi(rgb[1]);
	int_rgb[2] = ft_atoi(rgb[2]);
	if (int_rgb[0] < 0 || int_rgb[0] > 255 || int_rgb[1] < 0 || int_rgb[1] > 255
		|| int_rgb[2] < 0 || int_rgb[2] > 255)
		return (print_error("Ambient light RGB out of range [0, 255]", NULL));
	(*scene)->amb_light = malloc(sizeof(t_amb_light));
	if (!(*scene)->amb_light)
		return (print_error("Error allocating memory for ambient light", NULL));
	(*scene)->amb_light->ratio = ratio;
	(*scene)->amb_light->rgb[0] = int_rgb[0];
	(*scene)->amb_light->rgb[1] = int_rgb[1];
	(*scene)->amb_light->rgb[2] = int_rgb[2];
	free_array(&rgb);
}

static void	set_light(t_scene **scene, char **tokens)
{
	char	**coord;
	int		brightness;

	coord = ft_split(tokens[1], ',');
	brightness = ft_atod(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
		return (print_error("Light brightness out of range [0.0, 1.0]", NULL));
	(*scene)->light = malloc(sizeof(t_light));
	if (!(*scene)->light)
		return (print_error("Error allocating memory for light", NULL));
	(*scene)->light->coord[0] = ft_atod(coord[0]);
	(*scene)->light->coord[1] = ft_atod(coord[1]);
	(*scene)->light->coord[2] = ft_atod(coord[2]);
	(*scene)->light->brightness = brightness;
	free_array(&coord);
}

void	create_environment(char *line, t_scene **scene)
{
	char	**tokens;
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	tokens = ft_split(trimmed, ' ');
	if (!ft_strcmp(tokens[0], "A"))
		set_amb_light(scene, tokens);
	else if (!ft_strcmp(tokens[0], "C"))
		set_camera(scene, tokens);
	else if (!ft_strcmp(tokens[0], "L"))
		set_light(scene, tokens);
	free(trimmed);
	free_array(&tokens);
}
