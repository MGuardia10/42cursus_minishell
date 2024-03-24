/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:23:48 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/24 22:18:22 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	isdelimiter(char c)
{
	if (c == '\0' || c == ' ' || c == '"' || c == '\'' || c == '\n')
		return (0);
	return (1);
}

bool	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

t_redir isredir(char *token)
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
