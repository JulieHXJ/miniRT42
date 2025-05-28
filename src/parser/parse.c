/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/28 16:04:30 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	parser(char *fname, t_scene **scene, t_gc_object **gc_list)
{
	int		fd;
	char	*line;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file", NULL), false);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[0] != '#' && line[0] != '\n')
		{
			if ((line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
				&& !create_environment(line, scene, gc_list))
				return (free(line), false);
			else if (!create_objects(line, scene, gc_list))
				return (free(line), false);
		}
		free(line);
	}
	return (close(fd), true);
}

