/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:50:28 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/17 19:28:11 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_builtins(t_shell *shell, char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(shell->cmds->args));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell->envi, shell->home, shell->cmds->args[0]));
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
