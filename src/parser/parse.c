/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/07/04 14:14:36 by xhuang           ###   ########.fr       */
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

// change all tabs in string into spaces for gc_split
char	*tab_to_space(char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	i = 0;
	while (new_str[i])
	{
		if (new_str[i] == '\t')
			new_str[i] = ' ';
		i++;
	}
	return (new_str);
}

static bool	parse_line(char *line, t_scene **scene, t_gc_object **gc_list)
{
	char	*start;

	start = line;
	while (*start == ' ')
		start++;
	if (!*start || *start == '#' || *start == '\n')
		return (true);
	if (*start == 'A' || *start == 'C' || *start == 'L')
		return (create_environment(line, scene, gc_list));
	else
		return (create_objects(line, scene, gc_list));
}

bool	parser(int fd, t_scene **scene, t_gc_object **gc_list)
{
	char	*line;
	char	*temp;
	bool	flag;

	flag = true;
	while (flag)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = tab_to_space(line);
		free(line);
		line = temp;
		flag = parse_line(line, scene, gc_list);
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
