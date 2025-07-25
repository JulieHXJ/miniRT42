/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/07/11 18:04:17 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief validate number of arguments and file format.
 */
static bool	valid_file(int ac, char **av, int *fd)
{
	size_t	len;

	if (ac != 2 || !av[1])
		return (print_error(USAGE_MSG, NULL), false);
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 3, ".rt", 3) != 0)
		return (print_error("Incorrect file format", NULL), false);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (print_error("Failed to open file", NULL), false);
	return (true);
}

static void	viewport_init(t_viewport *vp)
{
	vp->fov = 60.0 * M_PI / 180.0;
	vp->aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	vp->view_width = 0.0;
	vp->view_height = 0.0;
	vp->up = new_vector(0, 0, 0);
	vp->right = new_vector(0, 0, 0);
	vp->normal = new_vector(0, 0, 0);
	vp->up_left_corner = new_vector(0, 0, 0);
}

static void	camera_init(t_scene *scene)
{
	scene->camera.origin = new_vector(0, 0, 0);
	scene->camera.direction = vec_normal(new_vector(0, -1, 0));
	scene->camera.fov = 60.0;
	scene->camera.cam_num = 0;
	viewport_init(&scene->camera.viewport);
}

/**
 * @brief Allocates and initializes a new scene
 *
 * @param list Garbage collector list for tracking mallocs
 * @return t_scene* Pointer to the initialized scene,
	or NULL if allocation fails
 */
static t_scene	*scene_init(t_gc_object **list)
{
	t_scene	*scene;

	scene = gc_alloc(sizeof(t_scene), list);
	if (!scene)
		return (NULL);
	scene->amb_light.ratio = 0.0;
	scene->amb_light.color = (t_color){0, 0, 0};
	scene->amb_light.amb_num = 0;
	scene->lights = NULL;
	scene->obj = NULL;
	scene->mlx = NULL;
	scene->img = NULL;
	camera_init(scene);
	return (scene);
}

int	main(int ac, char **av)
{
	t_gc_object	*gc_list;
	t_scene		*scene;
	int			fd;

	printf("Hook usage: %s\n", HOOK);
	gc_list = NULL;
	if (!valid_file(ac, av, &fd))
		return (1);
	scene = scene_init(&gc_list);
	if (!parser(fd, &scene, &gc_list))
		return (gc_free(gc_list), 1);
	if (!prepare_render(scene, &gc_list) && scene->mlx)
		return (mlx_terminate(scene->mlx), gc_free(gc_list), 1);
	free_color_buffer(scene->render.color, scene->img->height);
	if (!ft_strcmp(MODE, "TEXTURE"))
	{
		while (scene->obj)
		{
			if (scene->obj->tex.png)
				mlx_delete_texture(scene->obj->tex.png);
			scene->obj = scene->obj->next;
		}
	}
	mlx_terminate(scene->mlx);
	return (gc_free(gc_list), 0);
}
