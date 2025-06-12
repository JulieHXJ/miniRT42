/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:25:22 by dchrysov          #+#    #+#             */
/*   Updated: 2025/06/12 11:31:23 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*gc_alloc(size_t size, t_gc_object **gc_list)
{
	void		*mem;
	t_gc_object	*obj;

	mem = malloc(size);
	if (!mem)
		return (gc_free(*gc_list), NULL);
	obj = malloc(sizeof(t_gc_object));
	if (!obj)
	{
		free(mem);
		return (gc_free(*gc_list), NULL);
	}
	obj->ptr = mem;
	obj->marked = false;
	obj->next = *gc_list;
	*gc_list = obj;
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

static char	*ft_next_word(char const **s, char c, t_gc_object **gc_list)
{
	char const	*start;
	char		*str;
	size_t		len;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	str = gc_alloc(sizeof(char) * (len + 1), gc_list);
	if (!str)
		return (NULL);
	ft_strlcpy(str, start, len + 1);
	return (str);
}

char	**gc_split(const char *s, char c, t_gc_object **gc_list)
{
	char	**res;
	size_t	word_count;
	size_t	i;

	if (!s || !*s)
		return (NULL);
	word_count = str_count(s, c);
	res = gc_alloc(sizeof(char *) * (word_count + 1), gc_list);
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = ft_next_word(&s, c, gc_list);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			return (NULL);
		}
		i++;
	}
	res[word_count] = NULL;
	return (res);
}
