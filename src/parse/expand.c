/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:27:29 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/24 21:09:09 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expenv(char *line, int i)
{
	char	*env;
	char	*exp_env;
	int		j;

	j = i;
	while (isdelimiter(line[i]) == 1)
		i++;
	env = ft_substr(line, j, i - j);
	if (!env)
		return (NULL);
	exp_env = getenv(env); 
	if (!exp_env)
		return ("");
	free(env);
	return (exp_env);
}

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

int	expand_line(t_shell *shell)
{
	char	*exp = NULL;
	int		i;
	int		j;
	int		f;

	j = 0;
	i = 0;
	f = 0;
	while (shell->line_read[i])
	{
		if (shell->line_read[i] == '"')
		{
			if (f == 0)
				f = 1;
			else if (f == 1)
				f = 0;
		}
		if (shell->line_read[i] == '$')
		{
			if (join_line(shell, &exp, i, j) == 1)
				return (1);
			if (join_expenv(&exp, expenv(shell->line_read, i + 1)) == 1)
				return (1);
			while (isdelimiter(shell->line_read[i]) == 1)
				i++;
			j = i;
		}
		if (shell->line_read[i] == '\'' && f == 0)
			while (shell->line_read[++i] != '\'');
		i++;
	}
	if (join_line(shell, &exp, i, j) == 1)
		return (1);
	free(shell->line_read);
	shell->line_read = exp;
	//printf("\n%s\n", shell->line_read);
	return (0);
}