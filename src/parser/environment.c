/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/21 19:19:43 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Check number range and parse position, orientation and fov
 */
static bool	set_camera(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	t_vec3	position;
	t_vec3	ori_vec;
	int		fov;

	if (!assign_vector(tokens[1], &position, gc_list))
		return (print_error("Camera position parse failed", gc_list), false);
	if (!assign_normal(tokens[2], &ori_vec, gc_list))
		return (print_error("Camera orientation parse failed", gc_list), false);
	fov = ft_atoi(tokens[3]);
	if (!in_range_int(fov, 0, 180))
		return (print_error("FOV out of range", gc_list), false);
	(*scene)->camera.position = position;
	(*scene)->camera.direction = vec_normalize(ori_vec);
	(*scene)->camera.fov = fov;
	return (true);
}

static bool	set_amb_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	double	ratio;
	t_color	color;

	ratio = ft_atod(tokens[1]);
	if (!valid_ratio(ratio))
		return (print_error("Ambient light ratio out of range", gc_list),
			false);
	if (!assign_color(tokens[2], &color, gc_list))
		return (print_error("Ambient light color parse failed", gc_list), false);
	(*scene)->amb_light = gc_alloc(sizeof(t_amb_light), gc_list);
	if (!(*scene)->amb_light)
		return (print_error("Ambient light allocation failed", gc_list), false);
	(*scene)->amb_light.ratio = ratio;
	(*scene)->amb_light.color = color;
	return (true);
}

/**

	* @brief Append a new light to the head of the linked list (because order doesn't matter)
 */
static void	append_light(t_light **head, t_light *new_light)
{
	if (!head || !new_light)
		return ;
	(new_light)->next = *head;
	*head = new_light;
}

static bool	set_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	double	brightness;
	t_vec3	pos;
	t_color	col;
	t_light *new_light;

	// Parse brightness, and color
	brightness = ft_atod(tokens[2]);
	if (!valid_ratio(brightness))
		return (print_error("Light brightness out of range", gc_list), false);
	if (!assign_vector(tokens[1], &pos, gc_list))
		return (print_error("Light position parse failed", gc_list), false);
	if (!assign_color(tokens[3], &col, gc_list))
		return (print_error("Light color parse failed", gc_list), false);
	// Allocate memory for the new light
	new_light = gc_alloc(sizeof(t_light), gc_list);
	if (!new_light)
		return (print_error("Light allocatione failed", gc_list), false);
	new_light->position = pos;
	new_light->color = col;
	new_light->brightness = brightness;
	// append to the list
	append_light(&(*scene)->light, new_light);
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
	if (!trimmed)
		return (print_error("Strtrim failed for environment", gc_list), false);
	tokens = gc_split(trimmed, ' ');
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Split failed for environment", gc_list), false);
	flag = true;
	if (tokens[0][0] == 'A' && !tokens[0][1])
		flag = set_amb_light(scene, tokens, gc_list);
	else if (tokens[0][0] == 'C' && !tokens[0][1])
		flag = set_camera(scene, tokens, gc_list);
	else if (tokens[0][0] == 'L' && !tokens[0][1])
		flag = set_light(scene, tokens, gc_list);
	else
	{
		print_error("Unknown environment identifier", tokens[0]);
		flag = false;
	}
	return (flag);
}
