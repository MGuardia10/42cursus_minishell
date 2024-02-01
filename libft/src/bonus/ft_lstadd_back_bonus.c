/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:22:33 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:49:14 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * The function `ft_lstadd_back` adds a new element to the end of a linked list.
 * 
 * @param lst A pointer to a pointer to the first element of a linked list.
 * @param new The "new" parameter is a pointer to a t_list structure that
 * represents the new node to be added to the end of the list.
 * 
 * @return The function does not explicitly return a value.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		aux = ft_lstlast(*lst);
		aux->next = new;
	}
	else
		*lst = new;
}
