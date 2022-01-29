/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marinabuenogarcia <mbueno-g@student.42.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:12:54 by marinabuenoga     #+#    #+#             */
/*   Updated: 2022/01/28 18:34:17 by marinabuenoga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	printf_error(char *message, char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str[i]);
	if (str)
		free(str);
	printf("Error: %s\n", message);
	exit(1);
}
