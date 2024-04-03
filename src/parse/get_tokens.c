/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:25:34 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/03 19:32:02 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Extracts a word from a line and stores it in the tokens array.
 *
 * This function extracts a word from the given line starting from the current
 * position indicated by the variable i. The word is stored in the tokens array
 * at the current position indicated by the variable j. The function continues
 * extracting characters from the line until it encounters a special character
 * or reaches the end of the line.
 *
 * @param tokens The array to store the extracted word.
 * @param line The line from which to extract the word.
 * @param i A pointer to the current position in the line.
 * @param j A pointer to the current position in the tokens array.
 * @return 0 if the word was successfully extracted and stored, 1 otherwise.
 */
int	get_word(char **tokens, char *line, int *i, int *j)
{
	int		last;

	last = *i;
	while (line[*i] && !is_special_char(line[*i]))
		*i += 1;
	tokens[*j] = ft_substr(line, last, *i - last);
	if (!tokens[*j])
		return (1);
	*i -= 1;
	tokens[*j] = check_next_quotes(line, tokens, i, *j);
	if (!tokens[*j])
		return (1);
	*j += 1;
	return (0);
}

/**
 * Parses a given line into tokens.
 *
 * @param line The line to be parsed.
 * @return An array of tokens.
 *         Returns NULL if memory allocation fails or if an error occurs 
 * 		   during parsing.
 */
char	**get_tokens(char *line)
{
	int		i;
	int		j;
	char	**tokens;

	i = 0;
	j = 0;
	tokens = (char **)malloc(sizeof(char *) * (num_of_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		if (!is_special_char(line[i]))
		{
			if (get_word(tokens, line, &i, &j) == 1)
				return (NULL);
		}
		else
		{
			if (handle_special_char(line, tokens, &i, &j) == 1)
				return (NULL);
		}
	}
	tokens[j] = NULL;
	return (tokens);
}
