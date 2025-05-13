/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:25:22 by dchrysov          #+#    #+#             */
/*   Updated: 2025/05/13 16:54:40 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*gc_alloc(size_t size, t_gc_object **gc_list)
{
	void		*mem;
	t_gc_object	*obj;

	mem = malloc(size);
	if (!mem)
		return (gc_free(*gc_list), NULL);// Free all previously allocated memory if allocation fails
	obj = malloc(sizeof(t_gc_object));
	if (!obj)
	{
		free(mem); // Free the allocated memory for `mem` before returning
		return (gc_free(*gc_list), NULL);
	}
	obj->ptr = mem;
	obj->marked = false;
	obj->next = *gc_list;
	*gc_list = obj; // Update the head of the garbage collection list
	return (mem);
}

void	gc_mark(void *ptr, t_gc_object *gc_list)
{
	t_gc_object	*obj;

	obj = gc_list;
	while (obj)
	{
		if (obj->ptr == ptr)
		{
			obj->marked = true;
			break ;
		}
		obj = obj->next;
	}
}

void	gc_free(t_gc_object *gc_list)
{
	t_gc_object	**obj;
	t_gc_object	*unreached;

	obj = &gc_list;
	while (*obj)
	{
		if (!(*obj)->marked)
		{
			free((*obj)->ptr);
			unreached = *obj;
			*obj = (*obj)->next;
			free(unreached);
		}
		else
		{
			(*obj)->marked = false;
			obj = &(*obj)->next;
		}
	}
}
