/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 12:25:37 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Set up the viewport based on the camera parameters
 * @note The viewport is the scene that the camera can see.
 */
void	set_viewport(t_viewport *vp, t_camera *camera)
{
	t_vec3	world_up;
	t_vec3	screen_center;
	t_vec3	half_width;
	t_vec3	half_height;

	world_up = new_vector(0, 1, 0);
	if (fabs(vec_dot(camera->direction, world_up)) > 0.999)
		world_up = new_vector(0, 0, 1);
	vp->fov = camera->fov * M_PI / 180.0;
	vp->aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	vp->view_height = 2.0 * tan(vp->fov / 2.0);
	vp->view_width = vp->aspect_ratio * vp->view_height;
	vp->normal = camera->direction;
	vp->right = vec_normal(vec_cross(world_up, vp->normal));
	vp->up = vec_normal(vec_cross(vp->normal, vp->right));
	screen_center = vec_add(camera->origin, vec_scale(camera->direction, 1.0));
	half_width = vec_scale(vp->right, vp->view_width / 2.0);
	half_height = vec_scale(vp->up, vp->view_height / 2.0);
	vp->up_left_corner = vec_sub(vec_add(screen_center, half_height),
			half_width);
}

/**
 * @brief Check parameters and parse camera
 */
static bool	set_camera(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	t_vec3	position;
	t_vec3	ori_vec;
	int		fov;

	if ((*scene)->camera.cam_num != 0)
		return (print_error("Multiple cameras detected", *gc_list), false);
	if (array_size(tokens) != 4)
		return (print_error("Camera requires 3 parameters", *gc_list), false);
	position = new_vector(0, 0, 0);
	ori_vec = new_vector(0, 0, -1);
	fov = 0;
	if (!assign_vector(tokens[1], &position, gc_list))
		return (print_error("Camera position parse failed", *gc_list), false);
	if (!assign_normal(tokens[2], &ori_vec, gc_list))
		return (print_error("Camera orientation parse failed", *gc_list),
			false);
	fov = ft_atoi(tokens[3]);
	if (!in_range_int(fov, 0, 180))
		return (print_error("FOV out of range", *gc_list), false);
	(*scene)->camera.origin = position;
	(*scene)->camera.direction = vec_normal(ori_vec);
	(*scene)->camera.fov = fov;
	(*scene)->camera.cam_num++;
	set_viewport(&(*scene)->camera.viewport, &(*scene)->camera);
	return (true);
}

static bool	set_amb_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	float	ratio;
	t_color	color;

	if ((*scene)->amb_light.amb_num != 0)
		return (print_error("Multiple ambient lights detected", *gc_list),
			false);
	if (array_size(tokens) != 3)
		return (print_error("Ambient light requires 2 parameters", *gc_list),
			false);
	color = (t_color){0, 0, 0};
	ratio = ft_atod(tokens[1]);
	if (!valid_ratio(ratio))
		return (print_error("Ambient light ratio out of range", *gc_list),
			false);
	if (!assign_color(tokens[2], &color, gc_list))
		return (print_error("Ambient light color parse failed", *gc_list),
			false);
	(*scene)->amb_light.ratio = ratio;
	(*scene)->amb_light.color = color;
	(*scene)->amb_light.amb_num++;
	return (true);
}

/**
 * @brief Parse and create a light source
 * @note add light to the list if there is one, otherwith keep pointer to null
 */
static bool	set_light(t_scene **scene, char **tokens, t_gc_object **gc_list)
{
	static int	i = 0;
	float		brightness;
	t_vec3		pos;
	t_color		col;

	if (array_size(tokens) != 4)
		return (print_error("Light requires 3 parameters", *gc_list), false);
	brightness = ft_atod(tokens[2]);
	pos = new_vector(0, 0, 0);
	col = (t_color){0, 0, 0};
	if (!valid_ratio(brightness))
		return (print_error("Light brightness out of range", *gc_list), false);
	if (!assign_vector(tokens[1], &pos, gc_list))
		return (print_error("Light position parse failed", *gc_list), false);
	if (!assign_color(tokens[3], &col, gc_list))
		return (print_error("Light color parse failed", *gc_list), false);
	(*scene)->light = gc_alloc(sizeof(t_light), gc_list);
	if (!(*scene)->light)
		return (print_error("Light allocatione failed", *gc_list), false);
	(*scene)->light->id = i;
	(*scene)->light->position = pos;
	(*scene)->light->color = col;
	(*scene)->light->ratio = brightness;
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
		return (print_error("Strtrim failed for environment", *gc_list), false);
	tokens = gc_split(trimmed, ' ', gc_list);
	free(trimmed);
	if (!tokens || !tokens[0])
		return (print_error("Split failed for environment", *gc_list), false);
	flag = true;
	if (ft_strcmp(tokens[0], "A") == 0)
		flag = set_amb_light(scene, tokens, gc_list);
	else if (tokens[0][0] == 'C' && !tokens[0][1])
		flag = set_camera(scene, tokens, gc_list);
	else if (tokens[0][0] == 'L' && !tokens[0][1])
		flag = set_light(scene, tokens, gc_list);
	else
	{
		print_error("Unknown environment identifier", *gc_list);
		flag = false;
	}
	return (flag);
}
