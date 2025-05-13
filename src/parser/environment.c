/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/13 16:49:09 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Check number range and parse to camera struct
 */
static bool	set_camera(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	char	**vp;
    char	**orient;
    t_vec3	position;
    t_vec3	orientation;
    int		fov;

	vp = ft_split(tokens[1], ',');
	orient = ft_split(tokens[2], ',');
	d_orient[0] = ft_atod(orient[0]);
	d_orient[1] = ft_atod(orient[1]);
	d_orient[2] = ft_atod(orient[2]);
	if (d_orient[0] <= -1.0 || d_orient[0] >= 1.0 || d_orient[1] <= -1.0
		|| d_orient[1] >= 1.0 || d_orient[2] <= -1.0 || d_orient[2] >= 1.0)
		print_error("Camera orientation out of range [-1.0, 1.0]", gc_list);
	if (ft_atoi(tokens[3]) < 0 || ft_atoi(tokens[3]) > 180)
		print_error("Camera FOV out of range [0, 180]", gc_list);
	(*scene)->cam = gc_alloc(sizeof(t_camera), gc_list);
	(*scene)->cam->viewpoint[0] = ft_atod(vp[0]);
	(*scene)->cam->viewpoint[1] = ft_atod(vp[1]);
	(*scene)->cam->viewpoint[2] = ft_atod(vp[2]);
	(*scene)->cam->orient[0] = d_orient[0];
	(*scene)->cam->orient[1] = d_orient[1];
	(*scene)->cam->orient[2] = d_orient[2];
	(*scene)->cam->fov = ft_atoi(tokens[3]);
	return (free_array(&vp), free_array(&orient));
}

static bool	set_amb_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	char	**rgb;
	double	ratio;
	int		int_rgb[3];

	ratio = ft_atod(tokens[1]);
	if (ratio <= 0.0 || ratio >= 1.0)
		print_error("Ambient light ratio out of range [0.0, 1.0]", gc_list);
	rgb = ft_split(tokens[2], ',');
	int_rgb[0] = ft_atoi(rgb[0]);
	int_rgb[1] = ft_atoi(rgb[1]);
	int_rgb[2] = ft_atoi(rgb[2]);
	if (int_rgb[0] < 0 || int_rgb[0] > 255 || int_rgb[1] < 0 || int_rgb[1] > 255
		|| int_rgb[2] < 0 || int_rgb[2] > 255)
		print_error("Amb light RGB out of range [0, 255]", gc_list);
	(*scene)->amb_light = gc_alloc(sizeof(t_amb_light), gc_list);
	(*scene)->amb_light->ratio = ratio;
	(*scene)->amb_light->rgb[0] = int_rgb[0];
	(*scene)->amb_light->rgb[1] = int_rgb[1];
	(*scene)->amb_light->rgb[2] = int_rgb[2];
	free_array(&rgb);
}

static bool	set_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	char	**coord;
	int		brightness;

	coord = ft_split(tokens[1], ',');
	brightness = ft_atod(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
		return (print_error("Brightness out of range [0.0, 1.0]", gc_list));
	(*scene)->light = gc_alloc(sizeof(t_light), gc_list);
	(*scene)->light->coord[0] = ft_atod(coord[0]);
	(*scene)->light->coord[1] = ft_atod(coord[1]);
	(*scene)->light->coord[2] = ft_atod(coord[2]);
	(*scene)->light->brightness = brightness;
	free_array(&coord);
}

/**
 * @brief Parse and create environmental elements (A, C, L)
 * @return true if successful, false otherwise
 */
bool	create_environment(char *line, t_scene **scene, t_gc_object **gc_list)
{
	char	**tokens;
	char	*trimmed;
	bool	flag;

	trimmed = ft_strtrim(line, "\n");
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Memory allocation failed for environment", gc_list), false);
	flag = true;
	if (tokens[0][0] == 'A' && !tokens[0][1])
		flag = set_amb_light(scene, tokens, gc_list);
	else if (tokens[0][0] == 'C' && !tokens[0][1])
		flag = set_camera(scene, tokens, gc_list);
	else if (tokens[0][0] == 'L' && !tokens[0][1])
		flag = set_light(scene, tokens, gc_list);
	else
        print_error("Unknown environment identifier", tokens[0]);
	free_array(&tokens);
	return (flag);
}
