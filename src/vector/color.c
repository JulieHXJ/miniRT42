/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:22:35 by junjun            #+#    #+#             */
/*   Updated: 2025/05/13 15:11:54 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_color	color_init(int r, int g, int b)
{
    t_color c;
    
    c.r = r;
    c.g = g;
    c.b = b;
    return (c);
}

t_color color_scale(t_color c, double factor)
{
    t_color result;
    
    result.r = (int)(c.r * factor);
    result.g = (int)(c.g * factor);
    result.b = (int)(c.b * factor);
    return (result);
}

//change to c style
t_color color_add(t_color c1, t_color c2)
{
    t_color result;
    
    result.r = c1.r + c2.r > 255 ? 255 : c1.r + c2.r;
    result.g = c1.g + c2.g > 255 ? 255 : c1.g + c2.g;
    result.b = c1.b + c2.b > 255 ? 255 : c1.b + c2.b;
    return (result);
}


// Helper function to convert t_color to mlx color format
int convert_color(t_color color)
{
    return ((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff);
}