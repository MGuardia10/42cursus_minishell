/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:51:35 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:49:05 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/**
 * The function `ft_lstmap` takes a linked list `lst` and applies the function
 * `f` to each element, creating a new linked list with the modified elements.
 * 
 * @param lst A pointer to the first node of a linked list.
 * @param f f is a function pointer that takes a void pointer as input and
 * returns a void pointer. This function is applied to each element of the input
 * list to create a new element for the output list.
 * @param del The "del" parameter is a function pointer that takes a void pointer
 * as its argument and does some kind of cleanup or deletion operation on the
 * data pointed to by that pointer. It is used to free the memory allocated for
 * each element in the list in case of an error during the mapping process.
 * 
 * @return a pointer to a new linked list (`t_list`) that is created by applying
 * the function `f` to each element of the input linked list `lst`.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*node;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		set = f(lst->content);
		node = ft_lstnew(set);
		if (!node)
		{
			del(set);
			ft_lstclear(&list, del);
			return (list);
		}
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	return (list);
}
