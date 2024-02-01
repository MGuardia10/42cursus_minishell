/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:56:55 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:48:54 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * The function `ft_lstadd_front` adds a new node to the front of a linked list.
 * 
 * @param lst A pointer to a pointer to the first node of a linked list.
 * @param new The "new" parameter is a pointer to a t_list structure that
 * represents the new node to be added to the front of the list.
 * 
 * @return The function does not explicitly return a value.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
