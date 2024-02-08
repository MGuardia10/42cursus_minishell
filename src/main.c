/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/08 11:52:00 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"
#include "readline/readline.h"

char	*getdir(char *cmd)
{
	char	*dir;
	int		i;
	int		j;

	i = 2;
	while (cmd[i] != '\0' && cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[j] != '\0' && cmd[j] != ' ')
		j++;
	dir = ft_substr(cmd, i, j - i);
	if (!dir)
		return (NULL);
	return (dir);
}

int	main(int argc, char **argv)
{
	char	*str;

	str = NULL;
	(void)argv;
	if (argc == 0)
		return (EXIT_FAILURE);
	do
	{
		free(str);
		str = readline(">> ");
		if (ft_strcmp(str, "pwd") == 0)
			msh_pwd();
		else if (ft_strnstr(str, "cd", ft_strlen(str)))
			msh_cd(getdir(str));
		else if (ft_strcmp(str, "ls") == 0)
			system("ls");
		else if (ft_strnstr(str, "echo", ft_strlen(str))
				&& ft_strnstr(str, "-n", ft_strlen(str)) == NULL)
			msh_echo(ft_substr(str, 5, ft_strlen(str) - 5), 0);
		else if (ft_strnstr(str, "echo -n", ft_strlen(str)))
			msh_echo(ft_substr(str, 8, ft_strlen(str) - 8), 1);
	} while (ft_strcmp(str, "exit") != 0);
	free(str);
	return (EXIT_SUCCESS);
}
