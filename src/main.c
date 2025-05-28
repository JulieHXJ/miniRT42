/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/05/28 16:41:57 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_gc_object	*gc_list;
	t_scene		*scene;

	gc_list = NULL;
	if (!valid_file(ac, av))
		return (1);
	scene = scene_init(&gc_list);
	if (!parser(av[1], &scene, &gc_list))
		return (gc_free(gc_list), 1);
	// for checking the parser
	// print_obj(scene);
	// todo
	// if (!render(scene, &gc_list))
	// 	return (gc_free(gc_list), 1);
	// finish and clean up
	gc_free(gc_list);
	return (0);
}
