/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:18:50 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:49:03 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * `ft_lstlast` function returns a pointer to the last element of a linked list.
 * 
 * @param lst The parameter "lst" is a pointer to the first node of the list.
 * 
 * @return a pointer to the last node in the linked list.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*aux;

	aux = lst;
	while (lst != NULL)
	{
		aux = lst;
		lst = lst->next;
	}
	return (aux);
}
