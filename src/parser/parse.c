/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/12 18:37:55 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	parser(char *fname, t_scene **scene)
{
	int		fd;
	char	*line;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		print_error("Failed to open file", NULL);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[0] != '#')
		{
			if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
				create_environment(line, scene);//what it create fail
			else
				create_objects(line, scene);//what if create fail
		}
		free(line);
	}
	close(fd);
}
