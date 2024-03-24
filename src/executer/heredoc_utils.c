/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:52:13 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/24 16:28:20 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * checks if a given path is a directory and has executable permissions.
 * 
 * @param tmp_path a string that represents the path to be checked.
 * 
 * @return an integer value. If the `tmp_path` is not a directory, it returns 1 
 * after printing an error message. If the access to the `tmp_path` directory is
 * not executable, it also returns 1 after printing an error message. Otherwise,
 * it returns 0.
 */
int	check_access_tmp_folder(char *tmp_path)
{
	if (is_directory(tmp_path) == false)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: ", tmp_path);
		ft_fprintf(STDERR_FILENO, "is not a directory\n");
		return (1);
	}
	else if (access(tmp_path, X_OK) != 0)
	{
		perror("minishell: heredoc: /tmp");
		return (1);
	}
	return (0);
}

/**
 * creates a temporary file in the /tmp directory with a unique name based on an
 * incrementing number.
 * 
 * @return a string that represents the path to a unique temporary file.
 */
char	*create_temp_file(void)
{
	int		nbr;
	char	*nbr_str;
	char	*path;

	if (check_access_tmp_folder("/tmp"))
		return (NULL);
	nbr = 1;
	while (1)
	{
		nbr_str = ft_itoa(nbr);
		if (!nbr_str)
			return (NULL);
		path = ft_strjoin(TEMP_PATH, nbr_str);
		if (!path)
			return (free(nbr_str), NULL);
		if (access(path, X_OK) != 0)
		{
			free(nbr_str);
			break ;
		}
		free(nbr_str);
		free(path);
		nbr++;
	}
	return (path);
}
