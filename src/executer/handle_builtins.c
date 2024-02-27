/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:50:28 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/27 10:03:23 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_builtins(t_shell *shell, char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(shell->cmds->args));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell->envi, shell->cmds->args[0]));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(&shell->envi, shell->cmds->args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(&shell->envi, shell->cmds->args));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(&shell->envi, shell->cmds->args));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(shell));
	return (0);
}
