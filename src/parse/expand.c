/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:27:29 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/03 22:14:37 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Expands the exit status into a string representation.
 * If the global variable g_signal_status is set to SIGINT_FATHER,
 * it returns "1". Otherwise, it converts the exit status to a string
 * using the ft_itoa function and returns the result.
 *
 * @param exit_status The exit status to expand.
 * @return The expanded exit status as a string.
 */
char	*expand_exit_status(int exit_status)
{
	if (g_signal_status == SIGINT_FATHER)
	{
		g_signal_status = INTERACTIVE;
		return ("1");
	}
	return (ft_itoa(exit_status));
}

/**
 * Expands environment variables in the given shell command.
 * 
 * @param shell The shell structure containing the command and environment 
 * variables.
 * @param i The current index in the command string.
 * @param f A flag indicating whether to handle non-existent environment 
 * variables.
 * @return The expanded environment variable or a default value if it doesn't 
 * exist.
 */
char	*expenv(t_shell *shell, int *i, int f)
{
	char	*env;
	char	*exp_env;
	int		j;

	j = *i;
	if (shell->line_read[*i] == '?')
		return (*i += 1, expand_exit_status(shell->exit_status));
	if (shell->line_read[*i] == '$' || !ft_isalpha(shell->line_read[*i]))
		return (*i += 1, non_existent_env(f));
	while (isvalidchar(shell->line_read[*i]))
		*i += 1;
	if (j - *i == 0)
		return ("$");
	env = ft_substr(shell->line_read, j, *i - j);
	if (!env)
		return (NULL);
	exp_env = ft_getenv(shell->envi, env, &j);
	free(env);
	if (!exp_env)
		return (non_existent_env(f));
	return (exp_env);
}

/**
 * Checks if a character inside quotes is a starting or ending quote.
 * 
 * @param shell The shell structure.
 * @param i The index of the character being checked.
 * @param f The flag indicating if the character is inside quotes.
 *          0 - not inside quotes
 *          1 - inside quotes
 * 
 * @return 1 if the character is a starting quote, 0 if it is an ending quote,
 *         or the original flag value if the character is not a quote.
 */
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

/**
 * Expands variables in the shell's input line.
 *
 * This function takes a shell object, a pointer to a string to store the 
 * expanded line, and two integer pointers to keep track of the current 
 * position in the input line. It iterates through the input line character 
 * by character, expanding variables that are prefixed with a '$' symbol. 
 * The expanded line is stored in the 'exp' string.
 *
 * @param shell The shell object containing the input line and other shell data.
 * @param exp   Pointer to string to store the expanded line.
 * @param i     A pointer to the current position in the input line.
 * @param j     A pointer to the current position in the 'exp' array.
 * @return      0 if successful, 1 if an error occurred.
 */
int	expander(t_shell *shell, char **exp, int *i, int *j)
{
	int	f;

	f = 0;
	while (shell->line_read[*i])
	{
		f = check_inside_quotes(shell, *i, f);
		if (shell->line_read[*i] == '$')
		{
			if (join_line(shell, exp, *i, *j) == 1)
				return (1);
			*i += 1;
			if (join_expenv(exp, expenv(shell, i, f)) == 1)
				return (1);
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

/**
 * Expands the line by performing variable substitution and command 
 * substitution.
 * 
 * @param shell The shell structure.
 * @return 1 if an error occurs during expansion, 0 otherwise.
 */
int	expand_line(t_shell *shell)
{
	char	*exp;
	int		i;
	int		j;

	exp = NULL;
	j = 0;
	i = 0;
	if (expander(shell, &exp, &i, &j) == 1)
		return (1);
	if (clean_line(shell, &exp, i, j) == 1)
		return (1);
	return (0);
}
