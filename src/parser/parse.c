/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:15 by junjun            #+#    #+#             */
/*   Updated: 2025/05/09 15:28:53 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"



void	parser(char *fname, t_scene **scene)
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
			create_environment(line, scene);
		else if (line[0] == 'p' || line[0] == 's' || line[0] == 'c')
			create_objects(line, scene);
		free(line);
	}
	close(fd);
}
