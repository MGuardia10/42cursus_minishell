/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:50:31 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:48:55 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * The function `ft_lstclear` recursively clears a linked list and frees the
 * memory allocated for each node.
 * 
 * @param lst A pointer to a pointer to the first element of a linked list.
 * @param del The `del` parameter is a function pointer that points to a
 * function responsible for deleting the content of a node in the linked list.
 * The function takes a void pointer as its parameter, which represents the
 * content of the node.
 * 
 * @return The function does not return a value. It has a void return type.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
}
