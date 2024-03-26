/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:27:29 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 15:35:04 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expenv(t_shell *shell, int i, int f)
{
	char	*env;
	char	*exp_env;
	int		j;

	j = i;
	while (isdelimiter(shell->line_read[i]) == 1)
		i++;
	if (j - i == 0)
		return ("$");
	env = ft_substr(shell->line_read, j, i - j);
	if (!env)
		return (NULL);
	if (ft_strcmp(env, "?") == 0)
	{
		free(env);
		return (ft_itoa(shell->exit_status));
	}
	// exp_env = ft_getenv(shell->envi, env, &j);
	exp_env = getenv(env);
	free(env);
	if (!exp_env)
		return (non_existent_env(f));
	return (exp_env);
}

int	check_inside_quotes(t_shell *shell, int i, int f)
{
	if (shell->line_read[i] == '"')
	{
		if (f == 0)
			return (1);
		else if (f == 1)
			return (0);
	}
	return (f);
}

int	expander(t_shell *shell, char *exp, int *i, int *j)
{
	int	f;

	f = 0;
	while (shell->line_read[*i])
	{
		f = check_inside_quotes(shell, *i, f);
		if (shell->line_read[*i] == '$')
		{
			if (join_line(shell, &exp, *i, *j) == 1)
				return (1);
			*i += 1;
			if (join_expenv(&exp, expenv(shell, *i, f)) == 1)
				return (1);
			while (isdelimiter(shell->line_read[*i]) == 1)
				*i += 1;
			*j = *i;
			continue ;
		}
		if (shell->line_read[*i] == '\'' && f == 0)
			while (shell->line_read[++*i] != '\'')
				;
		*i += 1;
	}
	return (0);
}

int	expand_line(t_shell *shell)
{
	char	*exp;
	int		i;
	int		j;

	exp = NULL;
	j = 0;
	i = 0;
	if (expander(shell, exp, &i, &j) == 1)
		return (1);
	if (clean_line(shell, &exp, i, j) == 1)
		return (1);
	return (0);
}

//