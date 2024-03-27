/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/27 09:57:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * searches for a specific key in a linked list of environment variables and
 * returns the corresponding value.
 * 
 * @param envi a pointer to a linked list of environment variables.
 * @param key a string that represents the key for which you want to retrieve
 * the corresponding value from the environment.
 * @param flag a pointer to an integer. It is used to indicate whether the
 * specified key was found in the environment list or not.
 * 
 * @return a pointer to the value associated with the given key in the
 * environment list `envi`. If the key is found, it returns a pointer to the
 * value (excluding the "=" character which is used as a delimiter).
 */
char	*ft_getenv(t_env_list *envi, char *key, int *flag)
{
	t_env_list	*aux;

	aux = envi;
	*flag = 0;
	while (aux)
	{
		if (ft_strcmp(key, aux->content->key) == 0)
			return (aux->content->value + 1);
		aux = aux->next;
	}
	*flag = 1;
	return (NULL);
}

/**
 * checks if a path is a directory.
 * 
 * @param path a pointer to a string that represents the path of the directory
 * you want to check.
 * 
 * @return a boolean value indicating whether the given path is a directory or
 * not.
 */
bool	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

/**
 * removes temporary files that were created by the heredoc.
 * 
 * @param shell The `shell` parameter is a pointer to a structure `t_shell`.
 * @param cmds The `cmds` parameter is a pointer to an array of `t_command`
 * structures.
 * @param n_cmds The `n_cmds` parameter represents the number of commands in the
 * array `cmds`.
 * 
 * @return If the `unlink` function fails to remove a temporary file, an error
 * message will be printed using `perror`, and the function will return
 * without any specific return value.
 */
void	remove_temp_files(t_command *cmds, int n_cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_cmds)
	{
		j = 0;
		while (j < cmds[i].infile_count)
		{
			if (cmds[i].infiles[j].redir == HEREDOC && cmds[i].infiles[j].path)
				unlink(cmds[i].infiles[j].path);
			j++;
		}
		i++;
	}
}

/**
 * The function `clean_exit` removes temporary files and exits the program
 * with a failure status.
 * 
 * @param shell The `shell` parameter is a pointer to a `t_shell` struct.
 */
void	clean_exit(t_shell *shell, int exit_code)
{
	remove_temp_files(shell->cmds, shell->n_cmds);
	exit(exit_code);
}
