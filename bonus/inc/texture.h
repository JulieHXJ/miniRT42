/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:46:12 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/07 12:34:20 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_uv
{
	float	u;
	float	v;
}			t_uv;

typedef struct s_texture
{
	mlx_texture_t	*png;
	t_uv			uv;
}					t_texture;

#endif