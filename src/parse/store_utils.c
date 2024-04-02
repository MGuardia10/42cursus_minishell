/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:37:12 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/02 18:18:58 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Stores the executable command from the tokens array into the shell 
 * structure.
 * 
 * @param tokens The array of tokens containing the command and its arguments.
 * @param shell The shell structure to store the command in.
 * @param i A pointer to the current index in the tokens array.
 * @param j A pointer to the current index in the shell's cmds array.
 * @return Returns 0 if the command is successfully stored, 1 otherwise.
 */
void	store_exe(char **tokens, t_shell *shell, int *i, int *j)
{
	if (ft_strcmp(tokens[*i], "|") == 0)
	{
		*j += 1;
		*i += 1;
	}
	if (tokens[*i][0] == '"')
		shell->cmds[*j].exe = ft_strtrim(tokens[*i], "\"");
	else
		shell->cmds[*j].exe = ft_strtrim(tokens[*i], "'");
	if (!shell->cmds[*j].exe)
		exit(1);
}

/**
 * Stores the input file information in the command structure.
 * 
 * @param cmd The command structure to store the input file information in.
 * @param tokens The array of tokens containing the input file information.
 * @param i The index of the current token being processed.
 * @return Returns 0 if the input file information is successfully stored, 
 * 1 otherwise.
 */
int	store_infile(t_command *cmd, char **tokens, int *i)
{
	cmd->infiles[cmd->infile_count].redir = isredir(
			tokens[*i]);
	*i += 1;
	if ((cmd->infiles[cmd->infile_count].redir == HEREDOC)
		&& (tokens[*i][0] != '"' && tokens[*i][0] != '\''))
		cmd->infiles[cmd->infile_count].expheredoc = true;
	if (tokens[*i][0] == '"')
		cmd->infiles[cmd->infile_count].filename = ft_strtrim(
				tokens[*i], "\"");
	else
		cmd->infiles[cmd->infile_count].filename = ft_strtrim(
				tokens[*i], "'");
	if (!cmd->infiles[cmd->infile_count].filename)
		return (1);
	cmd->infile_count++;
	return (0);
}

/**
 * Stores the output file information in the command structure.
 * 
 * @param cmd The command structure to store the output file information in.
 * @param tokens The array of tokens containing the output file information.
 * @param i The index of the current token being processed.
 * @return Returns 0 if the output file information is successfully stored, 
 * 1 otherwise.
 */
int	store_outfile(t_command *cmd, char **tokens, int *i)
{
	cmd->outfiles[cmd->outfile_count].redir = isredir(tokens[*i]);
	*i += 1;
	if (tokens[*i][0] == '"')
		cmd->outfiles[cmd->outfile_count].filename = ft_strtrim(
				tokens[*i], "\"");
	else
		cmd->outfiles[cmd->outfile_count].filename = ft_strtrim(
				tokens[*i], "'");
	if (!cmd->outfiles[cmd->outfile_count].filename)
		return (1);
	cmd->outfile_count++;
	return (0);
}

/**
 * Stores input/output redirection information for a command.
 *
 * This function checks the type of redirection specified by the token at the
 * current index and stores the corresponding input/output file for the command
 * in the `cmds` array of the `shell` structure.
 *
 * @param tokens The array of tokens.
 * @param shell The shell structure.
 * @param i The current index in the tokens array.
 * @param j The index of the current command in the cmds array.
 * @return 1 if an error occurred, 0 otherwise.
 */
void	store_redir(char **tokens, t_shell *shell, int *i, int j)
{
	if (isredir(tokens[*i]) == IN || isredir(tokens[*i]) == HEREDOC)
	{
		if (store_infile(&shell->cmds[j], tokens, i) == 1)
			exit(1);
	}
	else if (isredir(tokens[*i]) == OUT || isredir(tokens[*i]) == APPOUT)
	{
		if (store_outfile(&shell->cmds[j], tokens, i) == 1)
			exit(1);
	}
}

/**
 * Stores an argument from the tokens array into the shell structure.
 * 
 * @param tokens The array of tokens.
 * @param shell The shell structure.
 * @param i The index of the token to store.
 * @param j The index of the command in the shell structure.
 * @return Returns 0 on success, 1 if the argument couldn't be stored.
 */
void	store_arg(char **tokens, t_shell *shell, int i, int j)
{
	if (tokens[i][0] == '"')
		shell->cmds[j].args[shell->cmds[j].args_count] = ft_strtrim(
				tokens[i], "\"");
	else
		shell->cmds[j].args[shell->cmds[j].args_count] = ft_strtrim(
				tokens[i], "'");
	if (!shell->cmds[j].args[shell->cmds[j].args_count])
		exit(1);
	shell->cmds[j].args_count++;
}
