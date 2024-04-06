/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:07:07 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/06 15:26:18 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Inverts the quotes in the given token.
 * If the token starts with a double quote, it replaces it with single quotes.
 * If the token starts with a single quote, it replaces it with double quotes.
 * 
 * @param tokens An array of strings representing tokens.
 * @param j The index of the token to invert.
 */
void	inv_quotes(char **tokens, int j)
{
	char	*aux1;
	char	*aux2;

	aux1 = ft_substr(tokens[j], 1, ft_strlen(tokens[j]) - 2);
	if (!aux1)
		exit(1);
	aux2 = NULL;
	if (tokens[j][0] == '"')
	{
		aux2 = ft_strjoin("'", aux1);
		free(aux1);
		aux1 = ft_strjoin(aux2, "'");
	}
	else if (tokens[j][0] == '\'')
	{
		aux2 = ft_strjoin("\"", aux1);
		free(aux1);
		aux1 = ft_strjoin(aux2, "\"");
	}
	free(aux2);
	free(tokens[j]);
	tokens[j] = ft_strdup(aux1);
	free(aux1);
}

/**
 * Changes the quote characters in a token.
 * If the token has invalid quotes, it calls the inv_quotes function to
 * invert quotes.
 * Otherwise, it matches the closing quote character with the opening quote 
 * character.
 * 
 * @param tokens The array of tokens.
 * @param j The index of the token to be modified.
 */
void	change_quote(char **tokens, int j)
{
	char	*aux1;
	char	*aux2;

	aux1 = NULL;
	aux2 = NULL;
	if (tokens[j][0] && tokens[j][0] == tokens[j][ft_strlen(tokens[j]) - 1]
		&& tokens[j][1] && tokens[j][1] == tokens[j][0]
		&& tokens[j][ft_strlen(tokens[j]) - 2]
		&& tokens[j][ft_strlen(tokens[j]) - 2] == tokens[j][0])
		inv_quotes(tokens, j);
	else
	{
		aux1 = ft_substr(tokens[j], 0, ft_strlen(tokens[j]) - 1);
		if (!aux1)
			exit(1);
		if (tokens[j][0] == '"')
			aux2 = ft_strjoin(aux1, "\"");
		else if (tokens[j][0] == '\'')
			aux2 = ft_strjoin(aux1, "'");
		free(aux1);
		free(tokens[j]);
		tokens[j] = ft_strdup(aux2);
		free(aux2);
	}
}

/**
 * Joins a quote character to the end of a token.
 * 
 * @param token A pointer to the token to modify.
 */
void	final_quote(char **token, int j)
{
	char	*aux;

	aux = NULL;
	if (token[j][0] == '"')
		aux = ft_strjoin(token[j], "\"");
	else if (token[j][0] == '\'')
		aux = ft_strjoin(token[j], "'");
	if (!aux)
		exit(1);
	free(token[j]);
	token[j] = ft_strdup(aux);
	free(aux);
}
