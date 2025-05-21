/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:00:36 by junjun            #+#    #+#             */
/*   Updated: 2025/05/21 14:49:53 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Check each element has correct number of parameters. (later will add bonus objects)
 *
 * @note A-3, C-4, L-3, sp-4, pl-4, cy-6.
 * (the correct range of numbers will be check in parser)
 */
static bool	check_ele_number(char **arr)
{
	size_t	arr_size;

	arr_size = array_size(arr);
	if (!arr || !arr[0] || arr[0][0] == '\0')
		return (false);
	if ((*arr)[0] == 'A' && arr_size == 3)
		return (true);
	else if ((*arr)[0] == 'C' && arr_size == 4)
		return (true);
	else if ((*arr)[0] == 'L' && arr_size == 3)
		return (true);
	else if (!ft_strcmp(arr[0], "sp") && arr_size == 4)
		return (true);
	else if (!ft_strcmp(arr[0], "pl") && arr_size == 4)
		return (true);
	else if (!ft_strcmp(arr[0], "cy") && arr_size == 6)
		return (true);
	else if (check_bonus(arr))//todo
	{
		return (true);
	}
	return (print_error("Invalid number of parameters in .rt file", NULL),
		false);
}

/**
 * @brief Check id(first word): A * 1, C * 1, L, pl, sp, cy mutiple, other objects for bonus
 */
static bool	check_file_contents(int fd)
{
	char	**arr;
	char	*line;
	int 	cam_num = 0;
	int		amb_num = 0;

	while ((line = get_next_line(fd)))
	{
		arr = ft_split(line, ' ');
		if (arr[0] == NULL || arr[0][0] == '\n' || arr[0][0] == '#')
		{
			free_array(&arr);
			free(line);
			continue ;
		}
		if (!check_ele_number(arr))
			return (free_array(&arr), free(line), false);
        if (arr[0][0] == 'C')
            cam_num++;
        else if (arr[0][0] == 'A')
            amb_num++;
		free_array(&arr);
		free(line);
	}
	if (cam_num != 1 || amb_num != 1)
		return (print_error("Only 1 camera or ambient light is allowed", NULL), false);
	return (true);
}

/**
 * @brief validate file name and content
 * @return true is it's valid file
 */
bool	valid_file(int ac, char **av)
{
	int		fd;
	size_t	len;
	char *line;

	if (ac != 2 || !av[1])
		return (print_error(USAGE_MSG, NULL), false);
	// check file name
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 3, ".rt", 3) != 0)
		return (print_error("Incorrect file format", NULL), false);
	// try to open file
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file", NULL), false);
	//check empty file
	line = get_next_line(fd);
	if (!line)
		return (print_error("Empty file", NULL), close(fd), false);
	free(line);
	if (!check_file_contents(fd))
		return (close(fd), false);
	close(fd);
	return (true);
}
