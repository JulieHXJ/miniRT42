/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/04/30 15:58:16 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	// t_gc_object	*gc_list;
	int			fd;

	if (ac != 2 || !av[1])
		return (printf(USAGE_MSG), 1);
	fd = open(av[1], O_RDONLY);
	if (!invalid_file(av[1], fd))
		return (1);
	return (0);
}
