/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/05/07 11:35:04 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_gc_object	*gc_list;
	t_scene		*scene;

	if (!invalid_file(ac, av))
		return (1);
	gc_list = NULL;
	scene = scene_init(&gc_list);
	parser(av[1], &scene, &gc_list);
	print_obj(*scene);
	gc_sweep(&gc_list);
	return (0);
}
