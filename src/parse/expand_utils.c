/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:38:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/31 11:05:46 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Extracts a substring from the input line and appends it to the given string.
 * 
 * @param shell The shell structure containing the input line.
 * @param exp   A pointer to the string to which the extracted substring will 
 * be appended.
 * @param i     The ending index of the substring (exclusive).
 * @param j     The starting index of the substring (inclusive).
 * @return      0 if the extraction and appending is successful, 1 otherwise.
 */
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

/**
 * Returns a string representing a non-existent environment variable.
 * 
 * @param f An integer flag indicating the type of non-existent environment 
 * variable.
 * If f is 1, an empty string is returned. Otherwise, a string 
 * containing double quotes is returned.
 * @return A string representing a non-existent environment variable.
 */
char	*non_existent_env(int f)
{
	if (f == 1)
		return (ft_strdup(""));
	else
		return (ft_strdup("\"\""));
}

/**
 * Cleans the line by joining the expanded tokens and updating the shell's 
 * line_read.
 * 
 * @param shell The shell structure.
 * @param exp The pointer to the expanded line.
 * @param i The starting index of the tokens to join.
 * @param j The ending index of the tokens to join.
 * @return 1 if an error occurred during joining, 0 otherwise.
 */
int	clean_line(t_shell *shell, char **exp, int i, int j)
{
	if (join_line(shell, exp, i, j) == 1)
		return (1);
	free(shell->line_read);
	shell->line_read = *exp;
	return (0);
}

/**
 * Joins a portion of the input line to the expanded string.
 * 
 * @param shell The shell structure.
 * @param exp The pointer to the expanded string.
 * @param i The end index of the portion to join.
 * @param j The start index of the portion to join.
 * @return 0 if successful, 1 if an error occurred.
 */
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

/**
 * Joins the given environment variable to the existing expanded string.
 *
 * @param exp The pointer to the expanded string.
 * @param env The environment variable to be joined.
 * @return 0 if successful, 1 otherwise.
 */
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
	// free(env);
	return (0);
}
