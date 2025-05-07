/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/07 11:08:45 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Init scene with the NULL env parameters and allocates memory for one
 * obj node.
 */
t_scene	*scene_init(t_gc_object **list)
{
	t_scene	*scene;

	scene = gc_alloc(sizeof(t_scene), list);
	scene->amb_light = NULL;
	scene->light = NULL;
	scene->cam = NULL;
	scene->obj = NULL;
	return (scene);
}

void	parser(char *fname, t_scene **scene, t_gc_object **gc_list)
{
	char	*line;
	int		fd;

	fd = open(fname, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			continue ;
		}
		if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
			create_environment(line, scene, gc_list);
		else if (line[0] == 'p' || line[0] == 's' || line[0] == 'c')
			create_objects(line, scene, gc_list);
		free(line);
	}
	close(fd);
}
