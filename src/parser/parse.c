/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/02 13:06:24 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_cylinder_ends(t_cylinder *c)
{
	t_vec3	half;

	half = vec_scale(c->direction, c->height * 0.5);
	c->bottom_center = vec_sub(c->center, half);
	c->top_center = vec_add(c->center, half);
}

bool	parser(int fd, t_scene **scene, t_gc_object **gc_list)
{
	char	*line;
	char	*start;
	bool	flag;

	flag = true;
	while (flag)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		start = line;
		while (*start == ' ' || *start == '\t')
			start++;
		if (*start && *start != '#' && *start != '\n')
		{
			if (*start == 'A' || *start == 'C' || *start == 'L')
				flag = create_environment(line, scene, gc_list);
			else
				flag = create_objects(line, scene, gc_list);
		}
		free(line);
		if (!flag)
			return (close(fd), false);
	}
	close(fd);
	if ((*scene)->camera.cam_num != 1 || (*scene)->amb_light.amb_num != 1)
		return (print_error("Only 1 camera or ambient light is allowed", NULL),
			false);
	return (flag);
}
