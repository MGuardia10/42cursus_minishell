/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_ascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:23:35 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/13 19:18:25 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_sort_ascii(char **array)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	while (array[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
				ft_change_pointers(&array[j], &array[j + 1]);
			j++;
		}
		i++;
	}
}
