/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:47:13 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 13:49:15 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_textures(t_scene scene)
{
	int			fd;
	char		*line;
	char		*trimmed;

	if (!ft_strcmp(MODE, "TEXTURE"))
	{
		fd = open("textures/list.txt", O_RDONLY);
		if (fd == -1)
			return ((void)print_error("Failed to open texture list", NULL));
		while (scene.obj)
		{
			if (scene.obj->type == SPHERE)
			{
				line = get_next_line(fd);
				if (!line)
					break ;
				trimmed = ft_strtrim(line, "\n");
				free(line);
				scene.obj->tex.png = mlx_load_png(trimmed);
				free(trimmed);
			}
			scene.obj = scene.obj->next;
		}
		close(fd);
	}
}
