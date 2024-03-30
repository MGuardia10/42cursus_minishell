/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/30 21:26:05 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*void	printall(t_shell *shell)
{
	for (int i = 0; i < shell->n_cmds; i++)
	{
		printf("-------------------------\n\n");
		printf("EXE COMANDO: \n%s\n\n", shell->cmds[i].exe);
		printf("ARGUMENTOS(%d): \n", shell->cmds[i].args_count);
		for (int j = 0; shell->cmds[i].args[j]; j++)
			printf("%s\n", shell->cmds[i].args[j]);
		printf("\nINFILES(%d): \n", shell->cmds[i].infile_count);
		for (int j = 0; j < shell->cmds[i].infile_count; j++)
		{
			printf("Tipo redir -> %u\n", shell->cmds[i].infiles[j].redir);
			printf("Filename -> %s\n", shell->cmds[i].infiles[j].filename);
			printf("Expheredoc -> %d\n\n", shell->cmds[i].infiles[j].expheredoc);
		}
		printf("OUTFILES(%d): \n", shell->cmds[i].outfile_count);
		for (int j = 0; j < shell->cmds[i].outfile_count; j++)
		{
			printf("Tipo redir -> %u\n", shell->cmds[i].outfiles[j].redir);
			printf("Filename -> %s\n\n", shell->cmds[i].outfiles[j].filename);
		}
		printf("-------------------------\n");
	}
}*/

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
	if (store_tokens(tokens, shell) == 1)
		exit(1);
//	printall(shell);
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
	add_history(shell->line_read);
	if (check_quotes(shell->line_read) == 1)
		return (1);
	if (expand_line(shell) == 1)
		exit(1);
	if (create_cmd_array(shell) == 1)
		return (1);
	return (0);
}
