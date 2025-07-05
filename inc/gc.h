/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:46:07 by dchrysov          #+#    #+#             */
/*   Updated: 2025/07/04 13:46:52 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdbool.h>

typedef struct s_gc_object
{
	void				*ptr;
	bool				marked;
	struct s_gc_object	*next;
}						t_gc_object;

void	*gc_alloc(size_t size, t_gc_object **gc_list);
void	gc_free(t_gc_object *gc_list);
char	**gc_split(const char *s, char c, t_gc_object **gc_list);
void	print_error(char *str, t_gc_object *gc_list);

#endif