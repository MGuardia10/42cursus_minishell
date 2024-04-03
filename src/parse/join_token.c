/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:39:14 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/03 19:31:05 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Changes the quote of a token.
 * 
 * This function takes a token as input and changes its quote. 
 * If the token starts with a double quote ("), it replaces the quote with a 
 * double quote at the end of the token.
 * If the token starts with a single quote ('), it replaces the quote with a 
 * single quote at the end of the token. 
 * 
 * @param token The token to change the quote of.
 */
void	change_quote(char *token)
{
	char	*aux;

	aux = NULL;
	aux = ft_substr(token, 0, ft_strlen(token) - 1);
	if (!aux)
		exit(1);
	if (token[0] == '"')
	{
		free(token);
		token = ft_strjoin(aux, "\"");
	}
	else if (token[0] == '\'')
	{
		free(token);
		token = ft_strjoin(aux, "'");
	}
	if (!token)
		exit(1);
	free(aux);
}

/**
 * Joins a quote character to the end of a token.
 * 
 * @param token A pointer to the token to modify.
 */
void	final_quote(char **token)
{
	char	*aux;

	aux = NULL;
	if (*token[0] == '"')
		aux = ft_strjoin(*token, "\"");
	else if (*token[0] == '\'')
		aux = ft_strjoin(*token, "'");
	if (!aux)
		exit(1);
	free(*token);
	*token = aux;
}

/**
 * @brief Matches and handles quotes in a token.
 *
 * This function checks if the token starts and ends with a quote character 
 * ('" or '\'').
 * If it does, it performs the necessary changes to handle the quotes properly.
 * If the 'f' parameter is 0, it trims the quotes from the token and returns 
 * the trimmed token.
 *
 * @param token The token to match and handle quotes for.
 * @param f     Flag indicating whether to trim the quotes from the token (0) 
 * or not (1).
 *
 * @return The modified token if 'f' is 0, otherwise the original token.
 */
char	*match_quotes(char *token, int f)
{
	char	*aux;

	aux = NULL;
	if (token[0] == '"' || token[0] == '\'')
	{
		if (token[ft_strlen(token) - 1] == '"'
			|| token[ft_strlen(token) - 1] == '\'')
			change_quote(token);
		else
			final_quote(&token);
	}
	if (f == 0)
	{
		aux = ft_strtrim(token, "\"'");
		if (!aux)
			return (NULL);
		free(token);
		token = aux;
	}
	return (token);
}

/**
 * Joins a word from the line with a token in the tokens array.
 * 
 * @param line The input line.
 * @param tokens The array of tokens.
 * @param i The current index in the line.
 * @param j The index of the token in the tokens array.
 */
void	join_word(char *line, char **tokens, int *i, int j)
{
	char	*aux;
	char	*new_part;
	int		last;

	last = *i;
	aux = ft_substr(tokens[j], 0, ft_strlen(tokens[j]) - 1);
	if (!aux)
		exit(1);
	free(tokens[j]);
	tokens[j] = aux;
	while (line[*i] && !is_special_char(line[*i]))
		*i += 1;
	new_part = ft_substr(line, last, (*i - last) + 1);
	if (!new_part)
		exit(1);
	aux = ft_strjoin(tokens[j], new_part);
	if (!aux)
		exit(1);
	free(tokens[j]);
	free(new_part);
	tokens[j] = aux;
}

/**
 * Checks if the next character in the line is a quote and handles it 
 * accordingly.
 * 
 * @param line The input line to be parsed.
 * @param tokens An array of tokens.
 * @param i A pointer to the current index in the line.
 * @param j The index of the token in the tokens array.
 * @return The modified token after handling the quotes, or NULL if an error 
 * occurred.
 */
char	*check_next_quotes(char *line, char **tokens, int *i, int j)
{
	int		f;

	f = 1;
	*i += 1;
	if (!ft_strchr(tokens[j], '"'))
	{
		put_quotes(&tokens[j]);
		f = 0;
	}
	while (line[*i] && !is_special_char_two(line[*i]))
	{
		if (line[*i] && (line[*i] == '"' || line[*i] == '\''))
			*i += 1;
		if (line[*i] && !is_special_char(line[*i]))
			join_word(line, tokens, i, j);
	}
	tokens[j] = match_quotes(tokens[j], f);
	if (!tokens[j])
		return (NULL);
	return (tokens[j]);
}
