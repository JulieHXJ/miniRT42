/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:38:15 by junjun            #+#    #+#             */
/*   Updated: 2025/06/11 17:29:39 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "intersect.h"
#include <pthread.h>

typedef struct s_viewpoint
{
    int width;  // Width of the viewport
    int height; // Height of the viewport
    t_vec3 up;
    t_vec3 right;
    
}				t_viewpoint;


# endif