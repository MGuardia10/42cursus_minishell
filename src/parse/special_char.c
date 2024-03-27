/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:39:53 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/27 00:53:37 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Handles parsing of quotes in the input line and stores the extracted
 * token in the tokens array.
 * 
 * This function checks if the current character in the input line is a 
 * double quote or a single quote.
 * If it is a double quote, it extracts the token enclosed within the 
 * double quotes and stores it in the cmds array.
 * If it is a single quote, it extracts the token enclosed within the 
 * single quotes and stores it in the cmds array.
 * 
 * @param line The input line to be parsed.
 * @param cmds The array to store the extracted tokens.
 * @param i A pointer to the current index in the input line.
 * @param j A pointer to the current index in the cmds array.
 * @return Returns 0 if the token is successfully extracted and stored, 
 * 1 otherwise.
 */
int	quotes_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = 0;
	if (line[*i] == '"')
	{
		*i += 1;
		last = *i;
		while (line[*i] && line[*i] != '"')
			*i += 1;
	}
	else if (line[*i] == '\'')
	{
		*i += 1;
		last = *i;
		while (line[*i] && line[*i] != '\'')
			*i += 1;
	}
	tokens[*j] = ft_substr(line, last - 1, (*i - last) + 2);
	if (!tokens[*j])
		return (1);
	*i += 1;
	*j += 1;
	return (0);
}

/**
 * Parses the input line and extracts the next token if it is an input 
 * file token.
 * 
 * @param line The input line to parse.
 * @param tokens An array to store the extracted tokens.
 * @param i A pointer to the current index in the line.
 * @param j A pointer to the current index in the tokens array.
 * @return 0 if the token is successfully extracted, 1 otherwise.
 */
int	infile_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = *i;
	if (line[*i + 1] == '<')
	{
		*i += 2;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	else
	{
		*i += 1;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	return (0);
}

/**
 * Parses the special character '>' in the given line and stores the 
 * resulting token in the tokens array.
 * 
 * @param line The input line to parse.
 * @param tokens The array to store the parsed tokens.
 * @param i The current index in the line.
 * @param j The current index in the tokens array.
 * @return 0 if successful, 1 if memory allocation fails.
 */
int	outfile_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = *i;
	if (line[*i + 1] == '>')
	{
		*i += 2;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	else
	{
		*i += 1;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	return (0);
}

/**
 * @brief Parses the pipe token in the given line and stores it in the 
 * tokens array.
 * 
 * This function is responsible for parsing the pipe token '|' in the 
 * given line and storing it in the tokens array. It updates the values 
 * of i and j accordingly.
 * 
 * @param line The input line to parse.
 * @param tokens The array to store the parsed tokens.
 * @param i A pointer to the current index in the line.
 * @param j A pointer to the current index in the tokens array.
 * @return Returns 0 if the pipe token is successfully parsed and stored, 
 * 1 otherwise.
 */
int	pipe_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = *i;
	*i += 1;
	tokens[*j] = ft_substr(line, last, *i - last);
	if (!tokens[*j])
		return (1);
	*j += 1;
	return (0);
}

/**
 * Handles special characters in the input line and updates the tokens array.
 * 
 * @param line The input line to parse.
 * @param tokens The array to store the parsed tokens.
 * @param i The current index in the input line.
 * @param j The current index in the tokens array.
 * @return 1 if a special character is successfully handled, 0 otherwise.
 */
int	handle_special_char(char *line, char **tokens, int *i, int *j)
{
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (quotes_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == '|')
	{
		if (pipe_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == '>')
	{
		if (outfile_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == '<')
	{
		if (infile_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == ' ')
		while (line[*i] == ' ')
			*i += 1;
	return (0);
}
