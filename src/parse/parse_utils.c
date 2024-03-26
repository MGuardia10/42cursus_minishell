/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:23:48 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:16 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	isdelimiter(char c)
{
	if (c == '\0' || c == ' ' || c == '"' || c == '\'' || c == '\n' || c == '$')
		return (0);
	return (1);
}

bool	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

t_redir	isredir(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (OUT);
	else if (ft_strcmp(token, "<") == 0)
		return (IN);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPOUT);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	return (NONE);
}

int	unexpected_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (isredir(tokens[i]) != NONE || ft_strcmp(tokens[i], "|") == 0)
		{
			if ((isredir(tokens[i + 1]) != NONE
					|| ft_strcmp(tokens[i + 1], "|") == 0)
				|| (ft_strcmp(tokens[i], "|") == 0 && i == 0))
			{
				ft_fprintf(
					STDERR_FILENO,
					"minishell: syntax error near unexpected token `%s'\n",
					tokens[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	count_cmd(char **tokens, t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1)
			count++;
		i++;
	}
	shell->n_cmds = count;
	return (count);
}
