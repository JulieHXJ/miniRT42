/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:00:36 by junjun            #+#    #+#             */
/*   Updated: 2025/05/06 11:11:18 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Check each element has correct number.
 * 
 * @note A-3, C-4, L-3, sp-4, pl-4, cy-6
 */
static bool	check_ele_number(char **arr)
{
	if ((*arr)[0] == 'A' && array_size(arr) == 3)
		return (true);
	else if ((*arr)[0] == 'C' && array_size(arr) == 4)
		return (true);
	else if ((*arr)[0] == 'L' && array_size(arr) == 3)
		return (true);
	else if ((*arr)[0] == 's' && array_size(arr) == 4)
		return (true);
	else if ((*arr)[0] == 'p' && array_size(arr) == 4)
		return (true);
	else if ((*arr)[0] == 'c' && array_size(arr) == 6)
		return (true);
	return (print_error("Misconfiguration in .rt file", NULL), false);
}

/**
 * @brief Check id(first word): A, C, L, pl, sp, cy only
 */
static bool	check_file_contents(char *fname, int fd)
{
	char	**arr;
	char	*line;

	fd = open(fname, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		arr = ft_split(line, ' ');
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
 * @brief Checks for .rt-file invalidity.
 * 
 * @note After passing the tests successfully, fd remains open.
*/
static void	check_file(char *fname, int fd)
{
	char	buf[1];

	if (!ft_strnstr(fname, ".rt", ft_strlen(fname)))
		return (close(fd), print_error("Incorrect file format", NULL));
	else if (fd == -1)
		return (close(fd), print_error("Failed to open file", NULL));
	else if (read(fd, buf, 1) == 0)
		return (close(fd), print_error("Empty file", NULL));
}

/**
 * @brief validate file name and content
 * @return true is it's invalid file
 */
bool	invalid_file(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	check_file(fname, fd);
	if (!check_file_contents(fname, fd))
		return (print_error("Misconfiguration in .rt file", NULL), false);
	close(fd);
	return (true);
}
