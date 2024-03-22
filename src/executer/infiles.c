/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:47 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/22 17:35:53 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_infiles(t_io_files *infiles, int i, bool *error)
{
	int	fd;

	if (infiles[i].redir == IN)
		fd = open(infiles[i].filename, O_RDONLY);
	else
		fd = open(infiles[i].path, O_RDONLY);
	if (fd < 0)
	{
		*error = true;
		if (infiles[i].redir == IN)
			ft_fprintf(STDERR_FILENO, "minishell: %s: ", infiles[i].filename);
		else
			ft_fprintf(STDERR_FILENO, "minishell: %s: ", infiles[i].path);
		return (perror(""), -1);
	}
	return (fd);
}

void	remove_temp_files(t_io_files *infiles, int in_count)
{
	int	i;

	i = 0;
	while (i < in_count)
	{
		if (infiles[i].redir == HEREDOC && infiles[i].path)
			unlink(infiles[i].path);
		i++;
	}
}

int	manage_infiles(t_shell *shell, t_io_files *infiles, int in_count)
{
	int		i;
	int		fd;
	bool	error;

	if (in_count == 0)
		return (STDIN_FILENO);
	i = 0;
	error = 0;
	if (resolve_heredoc(shell, infiles, i, in_count))
		return (-1);
	while (i < in_count)
	{
		fd = open_infiles(infiles, i, &error);
		if (error == true)
			return (remove_temp_files(infiles, in_count), -1);
		if (i != in_count - 1)
		{
			close(fd);
			if (infiles[i].redir == HEREDOC)
				unlink(infiles[i].path);
		}
		i++;
	}
	return (fd);
}
