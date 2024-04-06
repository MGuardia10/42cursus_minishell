/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:50:24 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/06 20:37:52 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * checks if a command is accessible and updates the status accordingly.
 * 
 * @param cmd is a pointer to a character array, which represents a command or
 * file path that you want to check for accessibility.
 * @param status a pointer to an integer that is used to store the status of
 * the command execution.
 * 
 * @return true if is a accesible file, and false if it´s a directory or the
 * file is not accessible.
 */
static bool	is_accessible(char *cmd, int *status)
{
	if (is_directory(cmd) == true)
		return (*status = 2, false);
	else if (access(cmd, X_OK) != 0)
		return (*status = 3, false);
	return (*status = 0, true);
}

/**
 * attempts to create a full path to the command by searching through the PATH
 * variable.
 * 
 * @param cmd represents the command that needs to be located in the system's
 * PATH variable.
 * @param envi represents a linked list containing environment variables.
 * @param status a pointer to an integer that is used to store the status of
 * the command execution.
 * 
 * @return If it successfully finds an accessible path for `cmd`, it will return
 * that full path. If it cannot find an accessible path, it will return `NULL`.
 */
static char	*create_path(t_shell *sh, char *cmd, t_env_list *envi, int *status)
{
	char	**paths;
	char	*path_slash;
	char	*path;
	int		i;

	paths = ft_split(ft_getenv(envi, "PATH", status), ':');
	if (!paths && *status == 1 && is_accessible(cmd, status) == true)
		return (cmd);
	else if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		if (!path_slash)
			(perror("malloc"), clean_exit(sh, EXIT_FAILURE));
		path = ft_strjoin(path_slash, cmd);
		if (!path)
			(perror("malloc"), clean_exit(sh, EXIT_FAILURE));
		if (is_accessible(path, status) == true)
			return (ft_free_matrix((void **)paths), free(path_slash), path);
		(free(path_slash), free(path));
	}
	ft_free_matrix((void **)paths);
	return (NULL);
}

/**
 * handles different types of path-related errors.
 * 
 * @param cmd represents the command that needs to be located in the system's
 * PATH variable.
 * @param envi represents a linked list containing environment variables.
 * @param status a pointer to an integer that is used to store the status of
 * the command execution.
 */
void	manage_path_errors(char *cmd, t_env_list *envi, int *status)
{
	if (*status == 2)
	{
		ft_dprintf(2, "minishell: %s: is a directory\n", cmd);
		*status = 126;
	}
	else if (*status == 3)
	{
		if (ft_getenv(envi, "PATH", status))
			ft_dprintf(2, "minishell: %s: command not found\n", cmd);
		else
			ft_dprintf(2, "minishell: %s: No such file or directory\n", cmd);
		*status = 127;
	}
	else
	{
		perror("minishell");
		*status = 1;
	}
}

/**
 * determines the full path of a command based on the input command and PATH
 * environment variable.
 * 
 * @param cmd represents the command that needs to be located in the system's
 * PATH variable.
 * @param envi represents a linked list containing environment variables.
 * @param status a pointer to an integer that is used to store the status of
 * the command execution. Possible status: 0 == OK, 1 == PATH env not found,
 * 2 == path found is a directory, 3 == path found not accessible.
 * 
 * @return either the input `cmd` if it contains a forward slash ('/'), or the
 * result of calling `create_path` function, or NULL If `create_path` fails to 
 * create a valid path.
 */
char	*find_path(t_shell *shell, char *cmd, t_env_list *envi, int *status)
{
	char	*path;

	if (!cmd || !cmd[0])
	{
		ft_dprintf(2, "minishell: : command not found\n");
		return (*status = 127, NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (is_accessible(cmd, status) == false)
		{
			if (*status == 2)
				return (ft_dprintf(2, "minishell: %s: is a directory\n", cmd), \
					*status = 126, NULL);
			if (*status == 3)
				return (ft_dprintf(2, "minishell: %s: No such file or directory\
					\n", cmd), *status = 127, NULL);
		}
		return (cmd);
	}
	path = create_path(shell, cmd, envi, status);
	if (!path)
		return (manage_path_errors(cmd, envi, status), NULL);
	return (path);
}
