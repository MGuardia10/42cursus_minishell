/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/13 19:12:59 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"
#include "../libft/inc/colors.h"

// void	leaks(void)
// {
// 	system("leaks -q minishell");
// }
// atexit(leaks);

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	
	(void)argv;
	if (argc == 0)
		return (EXIT_FAILURE);
	ft_memset(&shell, 0, sizeof(t_shell));
	if (create_env_list(&shell, env))
		return (ft_lstclear((t_list **)&shell.envi, free_env), EXIT_FAILURE);
	while (1)
	{
		shell.line_read = readline(BCYN"Minishell $ "RES);
		if (!shell.line_read || shell.line_read[0] == '\0')
			continue ;
		free(shell.line_read);
		// ft_lstclear((t_list **)&shell.string_list, free);
	}
	ft_lstclear((t_list **)&shell.envi, free_env);
	return (0);
}

/*
Para el parseo:
	- parsear de manera independiente si el una built nuestra, para que el input
	llegue limpio a las funciones especificas.
	- si no es built nuestra, parsear comando, flags, y de mas argumentos para
	pasarselos a el built que toque
*/