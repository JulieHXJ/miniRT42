/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:00:36 by junjun            #+#    #+#             */
/*   Updated: 2025/05/09 17:15:06 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Check each element has correct number of parameters.
 * 
 * @note A-3, C-4, L-3, sp-4, pl-4, cy-6. 
 * (the correct range of numbers will be check in parser)
 */
static bool	check_ele_number(char **arr)
{
	size_t arr_size;

	arr_size = array_size(arr);
	if (!arr || !arr[0] || arr[0][0] == '\0') 
		return false;
	if ((*arr)[0] == 'A' && arr_size == 3)
		return (true);
	else if ((*arr)[0] == 'C' && arr_size == 4)
		return (true);
	else if ((*arr)[0] == 'L' && arr_size == 3)
		return (true);
	

	//only checked the first letter, should be more sercure
	// else if ((*arr)[0] == 's' && arr_size == 4)
	// 	return (true);
	// else if ((*arr)[0] == 'p' && arr_size == 4)
	// 	return (true);
	// else if ((*arr)[0] == 'c' && arr_size == 6)
	// 	return (true);

	else if (!ft_strcmp(arr[0], "sp") && arr_size == 4)
		return (true);
	else if (!ft_strcmp(arr[0], "pl") && arr_size == 4)
		return (true);
	else if (!ft_strcmp(arr[0], "cy") && arr_size == 6)
		return (true);
	return (print_error("Misconfiguration in .rt file", NULL), false);
}

/**
 * @brief Check id(first word): A, C, L, pl, sp, cy only, but later we need other objects for bonus
 */
//but we can have multiple L, pl, sp, cy
static bool	check_file_contents(int fd)
{
	char	**arr;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		arr = ft_split(line, ' ');
		
		//for empty or comment line check
		if (arr[0] == NULL || arr[0][0] == '\n' || arr[0][0] == '#')
		{
			free_array(&arr);
			free(line);
			line = get_next_line(fd);
			continue;
		}
		
		
		if ((*arr)[0] != '\n')
		{
			if (!(!ft_strcmp(arr[0], "A") || !ft_strcmp(arr[0], "C")
					|| !ft_strcmp(arr[0], "L") || !ft_strcmp(arr[0], "pl")
					|| !ft_strcmp(arr[0], "sp") || !ft_strcmp(arr[0], "cy")))
				return (print_error("Misconfiguration in .rt filee", NULL),
					free_array(&arr), free(line), false);
			else if (!check_ele_number(arr))
				return (free_array(&arr), free(line), false);
		}
		free_array(&arr);
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

/**
 * @brief validate file name and content
 * @return true is it's valid file
 */
bool	valid_file(int ac, char **av)
{
	int	fd;
	size_t len;

	if (ac != 2 || !av[1])
		return (print_error(USAGE_MSG, NULL), false);

	//check file name
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 3, ".rt", 3) != 0)
		return (print_error("Incorrect file format", NULL), false);

	//try to open file
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file", NULL), false);

	//put empty file checking in parser

	if (!check_file_contents(fd))
		return(close(fd), false);
	close(fd);
	return (true);
}
