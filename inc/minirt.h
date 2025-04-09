/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:47 by junjun            #+#    #+#             */
/*   Updated: 2025/04/09 13:53:59 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
# include <fcntl.h>



#define USAGE_MSG "Usage: ./minirt scenes/<file_name>.rt"


bool invalid_file(char *str);


void print_error(char *str);

#endif