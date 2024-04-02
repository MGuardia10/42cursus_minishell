/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:34:54 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/02 18:36:47 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Checks if a character is a valid character for an enviroment variable name.
 *
 * @param c The character to check.
 * @return true if the character is alphanumeric or an underscore,
 * false otherwise.
 */
bool	isvalidchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/**
 * Checks if a character is a special character.
 *
 * @param c The character to check.
 * @return true if the character is a special character, false otherwise.
 */
bool	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

/**
 * Checks if a character is a special character.
 *
 * @param c The character to check.
 * @return true if the character is a special character, false otherwise.
 */
bool	is_special_char_two(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}
