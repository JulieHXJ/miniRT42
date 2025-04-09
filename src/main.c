/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:58:58 by junjun            #+#    #+#             */
/*   Updated: 2025/04/09 14:17:39 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_error(char *str)
{
	printf("%s\n", str);
	//free resoure
	exit();
}

int main(int ac, char **av)
{
	
	if (ac != 2 || !av[1])
	{
		printf(USAGE_MSG);
		return (1);
	}
	if (invalid_file(av[1]))
	{
		return(1);
	}
	if (!parse_input())
	{
		//free
		return(1);
	}

	
	
}