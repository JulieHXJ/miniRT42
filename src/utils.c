/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:16:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/01 14:59:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	size_t	i;
	size_t	size;

	if (!arr || !*arr)
		return ;
	size = array_size(*arr);
	i = -1;
	while (++i < size)
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	print_error(char *msg, t_gc_object *gc_list)
{
	printf("%sError%s: %s\n", RED, RST, msg);
	if (gc_list)
		gc_free(gc_list);
	exit(1);
}

/**
 * @brief Convert string to float
 * @param str String to convert (format: [-+]?[0-9]*\.?[0-9]+)
 * @return float value
 */
float	ft_atod(const char *s)
{
	float	res;
	float	frac;
	float	div;
	int		sign;

	sign = 1;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	res = 0;
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	frac = 0;
	div = 10;
	if (*s == '.')
	{
		s++;
		while (*s >= '0' && *s <= '9')
		{
			frac += (*s++ - '0') / div;
			div *= 10;
		}
	}
	return (sign * (res + frac));
}
