/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/08 12:42:44 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates an array of commands from the given shell input.
 * 
 * This function takes the shell input and tokenizes it using the 
 * get_tokens() function.
 * If the tokens are successfully obtained, it checks for any unexpected 
 * tokens using the unexpected_tokens() function.
 * If unexpected tokens are found, it frees the memory allocated for tokens 
 * and returns 1.
 * Otherwise, it initializes the necessary data structures for storing the 
 * tokens using the init_for_store() function.
 * Then, it stores the tokens in the shell data structure using the 
 * store_tokens() function. 
 * Finally, it frees the memory allocated for tokens 
 * and returns 0. 
 * 
 * @param shell A pointer to the shell data structure.
 * @return 0 if the command array is successfully created, 1 otherwise.
 */
int	create_cmd_array(t_shell *shell)
{
	char	**tokens;

	tokens = get_tokens(shell->line_read);
	if (!tokens)
		exit(1);
	if (unexpected_tokens(tokens) == 1)
	{
		ft_free_matrix((void *)tokens);
		return (1);
	}
	if (init_for_store(tokens, shell) == 1)
		exit(1);
	store_tokens(tokens, shell);
	ft_free_matrix((void *)tokens);
	return (0);
}

/**
 * Initializes the shell line by performing various operations.
 * 
 * @param shell The shell structure.
 * @return 0 if the initialization is successful, 1 otherwise.
 */
int	init_line(t_shell *shell)
{
	if (check_quotes(shell->line_read) == 1)
		return (1);
	if (expand_line(shell) == 1)
		exit(1);
	if (create_cmd_array(shell) == 1)
		return (1);
	return (0);
}
