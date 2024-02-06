/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/06 12:25:45 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"
#include "readline/readline.h"

int	main(int argc, char **argv)
{
	char *str = NULL;
	(void)argv;
	if (argc == 0)
		return (EXIT_FAILURE);
	do
	{
		str = readline(">> ");
		if (ft_strcmp(str, "pwd") == 0)
			msh_pwd();
		if (ft_strnstr(str, "cd", ft_strlen(str)) != NULL)
			msh_cd(ft_split(str, ' ')[1]);
	} while (ft_strcmp(str, "exit") != 0);
	free(str);
	return (EXIT_SUCCESS);
}
