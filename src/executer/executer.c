/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:52:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/23 10:08:03 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	executer(t_shell *shell)
{
	(void)shell;
	// Si hay heredoc, resolverlo previamente TODO
	return (0);
}

// if (ft_strncmp(first_node->content, "env", 3) == 0)
// 			ft_env(&shell.envi, second_node);
// 		if (ft_strncmp(shell.line_read, "unset", 5) == 0)
// 			ft_unset(&shell.envi, second_node);
// 		if (ft_strncmp(first_node->content, "export", 6) == 0)
// 			ft_export(&shell.envi, second_node);