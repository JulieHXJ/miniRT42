/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:47:13 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/07 18:27:24 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	assign_textures(t_scene scene)
{
	int			fd;
	char		*line;
	char		*trimmed;

	fd = open("textures/list.txt", O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open texture list", NULL), false);
	while (scene.obj)
	{
		if (scene.obj->type == SPHERE)
		{
			line = get_next_line(fd);
			if (!line)
				return (close(fd), false);
			trimmed = ft_strtrim(line, "\n");
			free(line);
			scene.obj->tex.png = mlx_load_png(trimmed);
			if (!scene.obj->tex.png)
				return (free(trimmed), close(fd), false);
			free(trimmed);
		}
		scene.obj = scene.obj->next;
	}
	close(fd);
	return (true);
}
