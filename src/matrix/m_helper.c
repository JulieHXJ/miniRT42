/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:33:44 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/05 16:37:31 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdbool.h>

/**
 * @brief Create a 4*4 identity matrix
 */
t_matrix	m_identity(void)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[i][j] = 1.0;
			else
				m.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (m);
}

/**
 * @brief Print matrix for debugging
 */
void	m_print(t_matrix m)
{
	int i, j;
	printf("Matrix:\n");
	for (i = 0; i < 4; i++)
	{
		printf("  [");
		for (j = 0; j < 4; j++)
		{
			printf("%8.3f", m.m[i][j]);
			if (j < 3)
				printf(" ");
		}
		printf("]\n");
	}
}

/**
 * @brief Compare two matrices for equality
 */
bool	m_equal(t_matrix a, t_matrix b)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (fabs(a.m[i][j] - b.m[i][j]) > EPSILON)
				return (false);
		}
	}
	return (true);
}
