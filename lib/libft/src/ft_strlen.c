/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:03:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/05/05 10:53:09 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

unsigned long	ft_strlen(const char *str)
{
	unsigned long	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}
