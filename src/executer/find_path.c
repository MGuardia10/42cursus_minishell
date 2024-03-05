/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:50:24 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/04 22:43:01 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function is_accessible checks if a command is accessible and updates the
 * status accordingly.
 * 
 * @param cmd The `cmd` parameter is a pointer to a character array, which
 * typically represents a command or file path that you want to check for
 * accessibility.
 * @param status The `status` parameter is a pointer to an integer that will be
 * used to store the status of the accessibility check.
 * 
 * @return The function `is_accessible` returns a boolean value (true or false)
 * based on the conditions specified in the code snippet.
 */
bool	is_accessible(char *cmd, int *status)
{
	if (is_directory(cmd) == true)
		return (*status = 2, false);
	else if (access(cmd, X_OK) != 0)
		return (*status = 3, false);
	return (*status = 0, true);
}

char	*create_path(char *cmd, t_env_list *envi, int *status)
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
			return (ft_putstr_fd("MALLOC error\n", 2), NULL);
		path = ft_strjoin(path_slash, cmd);
		if (!path)
			return (perror("minishell"), free(path_slash), NULL);
		if (is_accessible(path, status) == true)
			return (ft_free_matrix((void **)paths), free(path_slash), path);
		(free(path_slash), free(path));
	}
	return (NULL);
}

void	manage_path_errors(char *cmd, t_env_list *envi, int *status)
{
	if (*status == 2)
	{
		ft_fprintf(2, "minishell: %s: is a directory\n", cmd);
		*status = 126;
	}
	else if (*status == 3)
	{
		if (ft_getenv(envi, "PATH", status))
			ft_fprintf(2, "minishell: %s: command not found\n", cmd);
		else
			ft_fprintf(2, "minishell: %s: No such file or directory\n", cmd);
		*status = 127;
	}
	else
	{
		perror("minishell");
		*status = 1;
	}
}

/*
*	Status codes
*	0 == OK OR MALLOC ERROR if path == NULL
*	1 == PATH var not found
*	2 == path found is a directory
*	3 == path found is not accesible (permisos)
*	Status codes
*/
char	*find_path(char *cmd, t_env_list *envi, int *status)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (is_accessible(cmd, status) == false)
		{
			if (*status == 2)
				return (ft_fprintf(2, "minishell: %s: is a directory\n", cmd), \
					*status = 126, NULL);
			if (*status == 3)
				return (ft_fprintf(2, "minishell: %s: No such file or directory\
					\n", cmd), *status = 127, NULL);
		}
		return (cmd);
	}
	path = create_path(cmd, envi, status);
	if (!path)
		return (manage_path_errors(cmd, envi, status), NULL);
	return (path);
}
