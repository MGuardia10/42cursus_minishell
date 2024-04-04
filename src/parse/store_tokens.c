/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:20:44 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/04 23:51:38 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Stores the tokens in the shell structure.
 * 
 * This function takes an array of tokens and a shell structure as input.
 * It iterates through the tokens and determines whether each token is a 
 * executable, a redirection, or an argument.
 * If the token is a redirection, it calls the store_redir() function to 
 * handle it.
 * If the token is an executable, it calls the store_exe() function to 
 * handle it.
 * If the token is an argument, it calls the store_arg() function to handle it.
 * 
 * @param tokens An array of tokens.
 * @param shell The shell structure.
 * @return Returns 0 on success, 1 on failure.
 */
void	store_tokens(char **tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (isredir(tokens[i]) != NONE)
			store_redir(tokens, shell, &i, j);
		else if ((ft_strcmp(tokens[i], "|") == 0
				|| !shell->cmds[j].exe) && tokens[i][0]
				&& ft_strcmp(tokens[i], "\"\"") != 0)
			store_exe(tokens, shell, &i, &j);
		else if (tokens[i][0] && ft_strcmp(tokens[i], "\"\"") != 0)
			store_arg(tokens, shell, i, j);
		i++;
	}
}
