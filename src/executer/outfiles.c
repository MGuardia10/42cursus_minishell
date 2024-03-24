/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:02:23 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/24 16:01:43 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * open output files for writing in a shell program, handling both truncation
 * and appending modes.
 * 
 * @param outfiles The `outfiles` parameter is a pointer to a structure of type
 * `t_io_files`.
 * @param i an integer that represent which file to open.
 * @param error a boolean variable that is used to indicate whether an error
 * occurred during process of opening the files.
 * 
 * @return an integer representing the file descriptor of the output file. or -1
 * if there was an error.
 */
static int	open_outfiles(t_io_files *outfiles, int i, bool *error)
{
	int	fd;

	if (outfiles[i].redir == OUT)
		fd = open(outfiles[i].filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(outfiles[i].filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd < 0)
	{
		*error = true;
		ft_fprintf(STDERR_FILENO, "minishell: %s: ", outfiles[i].filename);
		return (perror(""), -1);
	}
	return (fd);
}

/**
 * handles opening and closing output files and returns the file descriptor or
 * pipe value.
 * 
 * @param outfiles The `outfiles` parameter is a pointer to a structure of type
 * `t_io_files`, which likely contains information about output files.
 * @param out_count represents the number of output files.
 * @param pipe an integer representing a file descriptor for a pipe. If there is
 * no pipe. pipe is -1.
 * 
 * @return an integer representing the file descriptor of the output file.
 */
int	manage_outfiles(t_io_files *outfiles, int out_count, int pipe)
{
	int		i;
	int		fd;
	bool	error;

	i = 0;
	error = false;
	fd = STDOUT_FILENO;
	while (i < out_count)
	{
		fd = open_outfiles(outfiles, i, &error);
		if (error == true)
			return (-1);
		if (i != out_count - 1)
			close(fd);
		i++;
	}
	if (fd == STDOUT_FILENO && pipe > 0)
		return (pipe);
	if (pipe > 0)
		close(pipe);
	return (fd);
}
