/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:39:14 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/05 13:30:34 by mguardia         ###   ########.fr       */
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

void	change_quote(char **tokens, int j)
{
	char	*aux1;
	char	*aux2;

	aux1 = NULL;
	aux2 = NULL;
	//if (token[0] == token[ft_strlen(token)])
	//	aux = ft_strdup(token);
	//else
	if (tokens[j][0] && tokens[j][0] == tokens[j][ft_strlen(tokens[j]) - 1] && tokens[j][1] && !(tokens[j][1] != tokens[j][0] && (tokens[j][1] == '"' || tokens[j][1] == '\'')) && tokens[j][ft_strlen(tokens[j]) - 2] && !(tokens[j][ft_strlen(tokens[j]) - 2] != tokens[j][0] && (tokens[j][ft_strlen(tokens[j]) - 2] == '"' || tokens[j][ft_strlen(tokens[j]) - 2] == '\'')))
	{
		inv_quotes(tokens, j);
		return ;
	}
	else
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
char	*match_quotes(char **token, int j, int f)
{
	char	*aux;

	aux = NULL;
	if (token[j][0] == '"' || token[j][0] == '\'')
	{
		if (token[j][ft_strlen(token[j]) - 1] == '"'
			|| token[j][ft_strlen(token[j]) - 1] == '\'')
			change_quote(token, j);
		else
			final_quote(token);
	}
	if (f == 0)
	{
		aux = ft_strtrim(token[j], "\"'");
		if (!aux)
			return (NULL);
		free(token[j]);
		token[j] = ft_strdup(aux);
		free(aux);
		if (!token[j])
			exit(1);
	}
	return (token[j]);
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
	new_part = ft_substr(line, last, (*i - last));
	if (!new_part)
		exit(1);
	aux = ft_strjoin(tokens[j], new_part);
	if (!aux)
		exit(1);
	free(tokens[j]);
	free(new_part);
	tokens[j] = aux;
}

void	join_quotes(char *line, char **tokens, int *i, int j)
{
	char	*aux;
	char	*new_part;
	int		last;

	last = *i;
	if (tokens[j][ft_strlen(tokens[j]) - 1] == '"' || tokens[j][ft_strlen(tokens[j]) - 1] == '\'')
	{
		aux = ft_substr(tokens[j], 0, ft_strlen(tokens[j]) - 1);
		if (!aux)
			exit(1);
		free(tokens[j]);
		tokens[j] = aux;
	}
	if (line[*i] && line[*i] == '"')
	{
		*i += 1;
		last++;
		while (line[*i] && line[*i] != '"')
			*i += 1;
	}
	else if (line[*i] && line[*i] == '\'')
	{
		*i += 1;
		last++;
		while (line[*i] && line[*i] != '\'')
			*i += 1;
	}
	new_part = ft_substr(line, last, (*i - last) + 1);
	if (!new_part)
		exit(1);
	aux = ft_strjoin(tokens[j], new_part);
	if (!aux)
		exit(1);
	free(tokens[j]);
	free(new_part);
	tokens[j] = aux;
	*i += 1;
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
	if (!ft_strchr(tokens[j], '"') && !ft_strchr(tokens[j], '\''))
	{
		put_quotes(tokens, j);
		f = 0;
	}
	while (line[*i] && !is_special_char_two(line[*i]))
	{
		if (line[*i] && (line[*i] == '"' || line[*i] == '\''))
		{
			f = 1;
			join_quotes(line, tokens, i, j);
		}
		if (line[*i] && !is_special_char(line[*i]))
			join_word(line, tokens, i, j);
	}
	tokens[j] = match_quotes(tokens, j, f);
	if (!tokens[j])
		return (NULL);
	return (tokens[j]);
}
