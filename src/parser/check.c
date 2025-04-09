/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:00:36 by junjun            #+#    #+#             */
/*   Updated: 2025/04/09 14:27:14 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* correct file type? handle empty file and missing file
*/
int check_file_name(char *str)
{
	//check file name
	if (ft_strncmp(str, ".rt") != 0)
	{
		print_error("Error: incorrect file format");
	}
	//file missing
	else if (!open(str))
	{
		close();
		print_error("Error: failed to open file")
	}
	//empty file
	else if (condition)
	{
		/* code */
	}
	return (0);
}

//check id(first word): A, C, L, pl, sp, cy only
int check_id()
{
	
}

//check each element has correct number: A-3, C-4, L-3, sp-4, pl-4, cy-6
int check_ele_number()
{
	
}


/**
 * @brief validate file name and content
 * @return true is it's invalid file
 */
bool invalid_file(char *str)
{
	if (check_file_name(str) == 1 || check_id() == 1 || check_ele_number() == 1)
	{
		return true;
	}

	return false;
}

