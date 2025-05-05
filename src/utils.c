/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:16:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/04/30 15:58:27 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

size_t	array_size(char **arr)
{
	size_t	size;

	size = 0;
	while (*arr)
	{
		size++;
		arr++;
	}
	return (size);
}

void	free_array(char ***arr)
{
	int	i;
	int	size;

	if (!arr || !*arr)
		return ;
	size = 0;
	i = -1;
	while (arr[++i])
		size++;
	i = -1;
	while (++i < size)
		free((*arr)[i]);
	free (*arr);
	*arr = NULL;
}

void	print_error(char *msg, t_gc_object *gc_list)
{
	printf("Error: %s\n", msg);
	if (gc_list)
		gc_sweep(gc_list);
	exit(1);
}
