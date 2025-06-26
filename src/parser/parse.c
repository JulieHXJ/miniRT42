/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/06/26 12:13:55 by dchrysov         ###   ########.fr       */
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

bool	parser(char *fname, t_scene **scene, t_gc_object **gc_list)
{
	int		fd;
	char	*line;
	bool	flag;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file", NULL), false);
	flag = true;
	while (flag)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[0] != '#' && line[0] != '\n')
		{
			if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
				flag = create_environment(line, scene, gc_list);
			else
				flag = create_objects(line, scene, gc_list);
			if (!flag)
			{
				free(line);
				break ;
			}
		}
		free(line);
	}
	return (close(fd), flag);
}

