/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:02:23 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/21 23:28:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	manage_outfiles(t_io_files *outfiles, int out_count)
{
	int		i;
	int		fd;
	bool	error;

	if (out_count == 0)
		return (STDOUT_FILENO);
	i = 0;
	while (i < out_count)
	{
		fd = open_outfiles(outfiles, i, &error);
		if (error == true)
			return (-1);
		if (i != out_count - 1)
			close(fd);
		i++;
	}
	return (fd);
}
