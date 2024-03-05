/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:12:07 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/04 22:40:12 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	- liberar antes de cada exit
	- si execve OK, lo de despues no se ejecuta
	- si execve KO, liberar y exit 1
	- Exit status posibles: 0, 1, 127 (no path OR not found), 126 (directorio)
*/
void	child_task(t_shell *shell)
{
	char	*path;
	char	**argv;
	char	**env;
	int		status;

	status = 0;
	path = find_path(shell->cmds->exe, shell->envi, &status);
	if (!path)
		exit(status);
	argv = create_argv(shell->cmds[0]);
	if (!argv)
		exit(1);
	// print_arr(argv);
	env = envi_to_arr(shell->envi);
	if (!env)
		exit(1);
	execve(path, argv, env);
	exit(status);
}

/*
	1. Crear proceso hijo
	2. Ejecutar tarea en el proceso hijo
	3. esperar al hijo finalizar
	4. 
*/
int	handle_simple_commmands(t_shell *shell)
{
	pid_t	pid;
	int		wstatus;

	(void)shell;
	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		child_task(shell);
	}
	if (pid > 0)
	{
		wait(&wstatus);
	}
	if (WIFEXITED(wstatus))
		printf("exit status child -> [ %d ]\n", WEXITSTATUS(wstatus));
	return (0);
}
