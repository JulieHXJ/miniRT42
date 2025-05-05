/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:00:36 by junjun            #+#    #+#             */
/*   Updated: 2025/05/05 11:09:48 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Checks for .rt-file invalidity.
 * 
 * @note After passing the tests successfully, fd remains open.
*/
static void	check_file(char *fname, int fd)
{
	char	buf[1];

	if (!ft_strnstr(fname, ".rt", ft_strlen(fname)))
		return (close(fd), print_error("incorrect file format", NULL));
	else if (fd == -1)
		return (close(fd), print_error("failed t open file", NULL));
	else if (read(fd, buf, 1) == 0)
		return (close(fd), print_error("Empty file", NULL));
}

/**
 * @brief Check each element has correct number.
 * 
 * @note A-3, C-4, L-3, sp-4, pl-4, cy-6
 */
static bool	check_ele_number(char **arr)
{
	if (*arr[0] == 'A' && array_size(arr) == 3)
		return (true);
	else if (*arr[0] == 'C' && array_size(arr) == 4)
		return (true);
	else if (*arr[0] == 'L' && array_size(arr) == 3)
		return (true);
	else if (*arr[0] == 's' && array_size(arr) == 4)
		return (true);
	else if (*arr[0] == 'p' && array_size(arr) == 4)
		return (true);
	else if (*arr[0] == 'c' && array_size(arr) == 6)
		return (true);
	return (print_error("Misconfiguration in .rt file", NULL), false);
}

/**
 * @brief Check id(first word): A, C, L, pl, sp, cy only
 */
static bool	check_file_contents(int fd)
{
	char	**tokens;
	char	*line;
	bool	res;

	line = get_next_line(fd);
	res = true;
	while (res && !*line)
	{
		tokens = ft_split(line, ' ');
		if ((ft_strlen(tokens[0]) == 1 && !ft_strncmp(tokens[0], "A", 1))
			|| (ft_strlen(tokens[0]) == 1 && !ft_strncmp(tokens[0], "C", 1))
			|| (ft_strlen(tokens[0]) == 1 && !ft_strncmp(tokens[0], "L", 1))
			|| (ft_strlen(tokens[0]) == 2 && !ft_strncmp(tokens[0], "pl", 2))
			|| (ft_strlen(tokens[0]) == 2 && !ft_strncmp(tokens[0], "sp", 2))
			|| (ft_strlen(tokens[0]) == 2 && !ft_strncmp(tokens[0], "cy", 2)))
		{
			if (!check_ele_number(tokens))
				break ;
			free_array(&tokens);
		}
		else
			res = false;
		line = get_next_line(fd);
	}
	return (res);
}

/**
 * @brief validate file name and content
 * @return true is it's invalid file
 */
bool	invalid_file(char *fname, int fd)
{
	check_file(fname, fd);
	if (!check_file_contents(fd))
		return (print_error("Misconfiguration in .rt file", NULL), false);
	return (true);
}
