/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:20:13 by xhuang            #+#    #+#             */
/*   Updated: 2025/06/05 16:34:08 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdio.h>

/**
 * Translation matrix:
 * [1  0  0  x]
 * [0  1  0  y]
 * [0  0  1  z]
 * [0  0  0  1]
 */
t_matrix	m_translation(double x, double y, double z)
{
	t_matrix	m;

	m = m_identity();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

/**
 * Scaling matrix:
 * [x  0  0  0]
 * [0  y  0  0]
 * [0  0  z  0]
 * [0  0  0  1]
 */
t_matrix	m_scaling(double x, double y, double z)
{
	t_matrix	m;

	m = m_identity();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return (m);
}

// rotation around x-axis
t_matrix	m_rotation_x(double angle)
{
	t_matrix	m;
	double		rad;
	double		cos_a;
	double		sin_a;

	m = m_identity();
	rad = angle * M_PI / 180.0;
	cos_a = cos(rad);
	sin_a = sin(rad);
	m.m[1][1] = cos_a;
	m.m[1][2] = -sin_a;
	m.m[2][1] = sin_a;
	m.m[2][2] = cos_a;
	return (m);
}

t_matrix	m_rotation_y(double angle)
{
	t_matrix	m;
	double		rad;
	double		cos_a;
	double		sin_a;

	m = m_identity();
	rad = angle * M_PI / 180.0;
	cos_a = cos(rad);
	sin_a = sin(rad);
	m.m[0][0] = cos_a;
	m.m[0][2] = sin_a;
	m.m[2][0] = -sin_a;
	m.m[2][2] = cos_a;
	return (m);
}

t_matrix	m_rotation_z(double angle)
{
	t_matrix m = m_identity();
	double rad = angle * M_PI / 180.0;
	double cos_a = cos(rad);
	double sin_a = sin(rad);

	m.m[0][0] = cos_a;
	m.m[0][1] = -sin_a;
	m.m[1][0] = sin_a;
	m.m[1][1] = cos_a;

	return (m);
}