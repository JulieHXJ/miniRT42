/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:38:15 by junjun            #+#    #+#             */
/*   Updated: 2025/06/25 18:03:54 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "vector.h"
// #include <pthread.h>

typedef struct s_material
{
	double specular;         // Specular reflection coefficient
	double reflective;       // Reflective coefficient
	double refractive_index; // Refractive index for transparency
	double roughness;        // Surface roughness for diffuse reflection
	double transparency;     // Transparency coefficient
}	t_material;




#endif