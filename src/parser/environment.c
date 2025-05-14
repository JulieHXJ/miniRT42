/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/14 21:31:01 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Check number range and parse position, orientation and fov
 */
static bool	set_camera(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	char	**vp;
	char	**orient;
	t_vec3	position;
	t_vec3	*ori_vec;
	int		fov;

	vp = gc_split(tokens[1], ',');
	orient = gc_split(tokens[2], ',');
	if (!vp || !orient)
		return (print_error("Camera parameters parse failed", gc_list), false);
	position = new_vector(ft_atod(vp[0]), ft_atod(vp[1]), ft_atod(vp[2]));
	ori_vec = new_vector(ft_atod(orient[0]), ft_atod(orient[1]),
			ft_atod(orient[2]));
	fov = ft_atoi(tokens[3]);
	if (!valid_normal(ori_vec) || !in_range_int(fov, 0, 180))
		return (free(orient_check),
			print_error("Camera parameters out of range", gc_list), false);
	(*scene)->camera = gc_alloc(sizeof(t_camera), gc_list);
	if (!(*scene)->camera)
		return (free(ori_vec),
			print_error("Failed to allocate memory for camera", gc_list),
			false);
	(*scene)->camera.position = position;
	(*scene)->camera.cam_orient = ori_vec;
	(*scene)->camera.fov = fov;
	return (true);
}

static bool	set_amb_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	char	**rgb;
	double	ratio;
	t_color	color;

	ratio = ft_atod(tokens[1]);
	rgb = gc_split(tokens[2], ',');
	if (!rgb)
		return (print_error("Ambient light RGB parse failed", gc_list), false);
	color = new_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (!valid_ratio(ratio) || !valid_color(color))
		return (print_error("Ambient light parameters out of range", gc_list),
			false);
	(*scene)->amb_light = gc_alloc(sizeof(t_amb_light), gc_list);
	if (!(*scene)->amb_light)
		return (print_error("Failed to allocate memory for ambient light",
				gc_list), false);
	(*scene)->amb_light.ratio = ratio;
	(*scene)->amb_light.color = color;
	return (true);
}

static bool	set_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	// char	**coord;
	// char	**color;
	// double	brightness;
	// t_color	color_vec;

	// coord = gc_split(tokens[1], ',');
	// color = gc_split(tokens[3], ',');
	// if (!coord || !color)
	// 	return (print_error("Light parse failed", gc_list), false);
	// brightness = ft_atod(tokens[2]);
	// color_vec = new_color(ft_atoi(color[0]), ft_atoi(color[1]),
	// 		ft_atoi(color[2]));
	// if (!valid_ratio(brightness) || !valid_color(color_vec))
	// 	return (print_error("Light parameters out of range", gc_list), false);
	// (*scene)->light = gc_alloc(sizeof(t_light), gc_list);
	// if (!(*scene)->light)
	// 	return (print_error("Failed to allocate memory for light", gc_list),
	// 		false);
	// (*scene)->light_num++;
	// (*scene)->light->position = new_vector(ft_atod(coord[0]), ft_atod(coord[1]),
	// 		ft_atod(coord[2]));
	// (*scene)->light->color = color_vec;
	// (*scene)->light->brightness = brightness;
	// (*scene)->light->next = NULL;
	// return (true);

	char	**coord;
    char	**color;
    double	brightness;
    t_color	color_vec;
    t_light	*new_light;

    // Split the position and color tokens
    coord = gc_split(tokens[1], ',', gc_list);
    color = gc_split(tokens[3], ',', gc_list);
    if (!coord || !color)
        return (print_error("Light parse failed", gc_list), false);

    // Parse position, brightness, and color
    brightness = ft_atod(tokens[2]);
    color_vec = new_color(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));

    // Validate brightness and color
    if (!valid_ratio(brightness) || !valid_color(color_vec))
        return (print_error("Light parameters out of range", gc_list), false);

    // Allocate memory for the new light
    new_light = gc_alloc(sizeof(t_light), gc_list);
    if (!new_light)
        return (print_error("Failed to allocate memory for light", gc_list), false);

    // Assign values to the new light
    new_light->position = new_vector(ft_atod(coord[0]), ft_atod(coord[1]), ft_atod(coord[2]));
    new_light->color = color_vec;
    new_light->brightness = brightness;

    // Link the new light to the existing list
    new_light->next = (*scene)->light;
    (*scene)->light = new_light;

    // Increment the light count
    (*scene)->light_num++;

    return (true);
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
	tokens = gc_split(trimmed, ' ');
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Memory allocation failed for environment",
				gc_list), false);
	flag = true;
	if (tokens[0][0] == 'A' && !tokens[0][1])
		flag = set_amb_light(scene, tokens, gc_list);
	else if (tokens[0][0] == 'C' && !tokens[0][1])
		flag = set_camera(scene, tokens, gc_list);
	else if (tokens[0][0] == 'L' && !tokens[0][1])
		flag = set_light(scene, tokens, gc_list);
	else
		print_error("Unknown environment identifier", tokens[0]);
	return (flag);
}
