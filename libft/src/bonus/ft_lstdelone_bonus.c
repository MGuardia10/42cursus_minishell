/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:40:46 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:48:57 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * The function `ft_lstdelone` deletes a single node from a linked list and
 * frees the memory associated with it.
 * 
 * @param lst The parameter `lst` is a pointer to a `t_list` structure.
 * @param del The "del" parameter is a function pointer that points to a
 * function responsible for deleting the content of a node in a linked list.
 * The function takes a void pointer as its parameter, which represents the
 * content of the node to be deleted.
 * 
 * @return The function does not return anything. It has a void return type.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}
