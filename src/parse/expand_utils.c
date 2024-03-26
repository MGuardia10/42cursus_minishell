/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:38:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:00 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	extract_from_line(t_shell *shell, char **exp, int i, int j)
{
	char	*extract;
	char	*aux;

	extract = ft_substr(shell->line_read, j, i - j);
	if (!extract)
		return (1);
	aux = ft_strjoin(*exp, extract);
	if (!aux)
		return (1);
	free(extract);
	free(*exp);
	*exp = aux;
	return (0);
}

char	*non_existent_env(int f)
{
	if (f == 1)
		return ("");
	else
		return ("\"\"");
}

int	clean_line(t_shell *shell, char **exp, int i, int j)
{
	if (join_line(shell, exp, i, j) == 1)
		return (1);
	free(shell->line_read);
	shell->line_read = *exp;
	return (0);
}

int	join_line(t_shell *shell, char **exp, int i, int j)
{
	if (!*exp)
	{
		*exp = ft_substr(shell->line_read, j, i);
		if (!*exp)
			return (1);
	}
	else if (extract_from_line(shell, &*exp, i, j) == 1)
		return (1);
	return (0);
}

int	join_expenv(char **exp, char *env)
{
	char	*aux;

	if (!env)
		return (1);
	aux = ft_strjoin(*exp, env);
	if (!aux)
		return (1);
	free(*exp);
	*exp = aux;
	return (0);
}
