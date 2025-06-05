/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_operation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:32:39 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/05 16:36:16 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

/**
 * @brief Multiply two 4x4 matrices
 * 
 */
t_matrix m_multiply(t_matrix a, t_matrix b)
{
	t_matrix result;
	int row, col, i;

	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			result.m[row][col] = 0.0;
			for (i = 0; i < 4; i++)
			{
				result.m[row][col] += a.m[row][i] * b.m[i][col];
			}
		}
	}
	return (result);
}


/**
 * @brief Calculate matrix transpose
 * 
 * Transpose flips matrix across diagonal: m[i][j] becomes m[j][i]
 * Used for transforming normals correctly
 */
t_matrix m_transpose(t_matrix m)
{
	t_matrix result;
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result.m[i][j] = m.m[j][i];
		}
	}
	return (result);
}