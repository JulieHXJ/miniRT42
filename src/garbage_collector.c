/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:25:22 by dchrysov          #+#    #+#             */
/*   Updated: 2025/04/30 15:58:00 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	*gc_alloc(size_t size, t_gc_object *gc_list)
{
	void		*mem;
	t_gc_object	*obj;

	mem = malloc(size);
	obj = malloc(sizeof(t_gc_object));
	if (!obj)
		return (gc_sweep(gc_list), NULL);
	obj->ptr = mem;
	obj->marked = false;
	obj->next = gc_list;
	gc_list = obj;
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

void	gc_sweep(t_gc_object *gc_list)
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
