/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:52:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/26 16:31:27 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	simple_cmds(t_shell *shell)
{
	if (is_builtin(shell->cmds->exe))
		return (handle_builtins(shell, shell->cmds->exe));
	else
		// return (handle_commmands());
		return (0);
}

int compound_cmds(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	executer(t_shell *shell)
{
	// Si hay heredoc, resolverlo previamente TODO
	// distinguir entre comandos simples - builtins o llamadas al sistema // comandos compuestos
	if (shell->n_cmds == 1)
		return (simple_cmds(shell));
	else
		return (compound_cmds(shell));
	return (0);
}
