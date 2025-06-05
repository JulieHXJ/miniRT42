/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:20:51 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/05 16:37:45 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
#include <math.h>

typedef struct s_matrix
{
	double	m[4][4];
}			t_matrix;

// Matrix creation functions
t_matrix	m_identity(void);
t_matrix	m_translation(double x, double y, double z);
t_matrix	m_scaling(double x, double y, double z);
t_matrix	m_rotation_x(double angle);
t_matrix	m_rotation_y(double angle);
t_matrix	m_rotation_z(double angle);

// Matrix operations
t_matrix	m_multiply(t_matrix a, t_matrix b);
t_matrix	m_inverse(t_matrix m);
t_matrix	m_transpose(t_matrix m);

// Vector-matrix operations
t_vec3		m_multiply_point(t_matrix m, t_vec3 p);
t_vec3		m_multiply_vector(t_matrix m, t_vec3 v);

// Helper functions
void		m_print(t_matrix m);
bool		m_equal(t_matrix a, t_matrix b);
#endif