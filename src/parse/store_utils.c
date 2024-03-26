/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:37:12 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:29 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	store_exe(char **tokens, t_shell *shell, int *i, int *j)
{
	if (*i != 0)
	{
		*j += 1;
		*i += 1;
	}
	if (tokens[*i][0] == '"')
		shell->cmds[*j].exe = ft_strtrim(tokens[*i], "\"");
	else
		shell->cmds[*j].exe = ft_strtrim(tokens[*i], "'");
	if (!shell->cmds[*j].exe)
		return (1);
	return (0);
}

int	store_infile(t_command *cmd, char **tokens, int *i)
{
	cmd->infile[cmd->infile_count].redir = isredir(
			tokens[*i]);
	*i += 1;
	if ((cmd->infile[cmd->infile_count].redir == HEREDOC)
		&& (tokens[*i][0] != '"' && tokens[*i][0] != '\''))
		cmd->infile[cmd->infile_count].expheredoc = true;
	if (tokens[*i][0] == '"')
		cmd->infile[cmd->infile_count].filename = ft_strtrim(
				tokens[*i], "\"");
	else
		cmd->infile[cmd->infile_count].filename = ft_strtrim(
				tokens[*i], "'");
	if (!cmd->infile[cmd->infile_count].filename)
		return (1);
	cmd->infile_count++;
	return (0);
}

int	store_outfile(t_command *cmd, char **tokens, int *i)
{
	cmd->outfile[cmd->outfile_count].redir = isredir(tokens[*i]);
	*i += 1;
	if (tokens[*i][0] == '"')
		cmd->outfile[cmd->outfile_count].filename = ft_strtrim(
				tokens[*i], "\"");
	else
		cmd->outfile[cmd->outfile_count].filename = ft_strtrim(
				tokens[*i], "'");
	if (!cmd->outfile[cmd->outfile_count].filename)
		return (1);
	cmd->outfile_count++;
	return (0);
}

int	store_redir(char **tokens, t_shell *shell, int *i, int j)
{
	if (isredir(tokens[*i]) == IN || isredir(tokens[*i]) == HEREDOC)
	{
		if (store_infile(&shell->cmds[j], tokens, i) == 1)
			return (1);
	}
	else if (isredir(tokens[*i]) == OUT || isredir(tokens[*i]) == APPOUT)
	{
		if (store_outfile(&shell->cmds[j], tokens, i) == 1)
			return (1);
	}
	return (0);
}

int	store_arg(char **tokens, t_shell *shell, int i, int j)
{
	if (tokens[i][0] == '"')
		shell->cmds[j].args[shell->cmds[j].args_count] = ft_strtrim(
				tokens[i], "\"");
	else
		shell->cmds[j].args[shell->cmds[j].args_count] = ft_strtrim(
				tokens[i], "'");
	if (!shell->cmds[j].args[shell->cmds[j].args_count])
		return (1);
	shell->cmds[j].args_count++;
	return (0);
}
