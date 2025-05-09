/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/05/09 16:38:45 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/**
 * @brief Init scene with the NULL env parameters and allocates memory for one
 * obj node.
 */
void	*scene_init(t_scene *scene)
{
	// t_scene	*scene;

	// scene = gc_alloc(sizeof(t_scene), list);
	scene->amb_light = NULL;
	scene->light = NULL;
	scene->cam = NULL;
	scene->obj = NULL;
}

static void minirt_init(t_minirt *mini, t_gc_object **list)
{
	mini->scene = gc_alloc(sizeof(t_scene), list);
	scene_init(mini->scene);
	mini->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MiniRT", true);
	if (!mini->mlx)
	{
		//free_minirt();
		exit(EXIT_FAILURE);
	}
}


int	main(int ac, char **av)
{
	t_gc_object		*gc_list;
	// t_scene			*scene;
	t_minirt		*minirt;

	if (!valid_file(ac, av))
		return (1);

	gc_list = NULL;
	minirt = gc_alloc(sizeof(t_minirt), gc_list);
	
	//to do scene_init and mlx_init
	minirt_init(minirt, gc_list);

	//want to change return value to bool
	parser(av[1], &minirt->scene, &gc_list);
	// if (!parser(av[1], &scene, &gc_list))
	// {
	// 	print_error("Parsing failed", gc_list);
	// 	return (1);
	// }

	//for checking the parser
	print_obj(*scene);

	
	// ray_tracing(scene);
	// lighting(scene);
	// img_init(scene);
	// draw_scene(scene);
	// mlx_image_to_window(scene->mlx, scene->image);
	// mlx_loop_hook(scene->mlx, update_hook, scene);
	// mlx_loop(scene->mlx);
	// mlx_terminate(scene->mlx);




	
	//free_scene();
	gc_free(&gc_list);
	return (0);
}
