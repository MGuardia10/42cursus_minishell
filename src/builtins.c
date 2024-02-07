/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:31:21 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/07 23:40:22 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

int	msh_pwd(void)
{
	char buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}

int	msh_cd(char *dir)
{
	if (!dir || dir[0] == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else if (chdir(dir) != 0)
	{
		perror(dir);
		free(dir);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	echoPrintEnv(char *msg, int *i)
{
	int		j;
	char	*env;
	char	*exp_env;
	
	j = 0;
	j = *i;
	while (msg[*i] != '\0' && msg[*i] != ' ')
		*i += 1;
	env = ft_substr(msg, j + 1, *i - j - 1);
	if (!env)
		return (EXIT_FAILURE);
	exp_env = getenv(env);
	if (exp_env)
		ft_printf("%s", exp_env);
	free(env);
	return (EXIT_SUCCESS);
}

int	echoWithQuotes(char *msg)
{
	int	i;

	i = 1;
	while (msg[i] != '\0' && msg[i] != '"')
	{
		if (msg[i] == '$')
		{
			if (echoPrintEnv(msg, &i) == 1)
				return (EXIT_FAILURE);
		}
		ft_printf("%c", msg[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}


int	echoNoQuotes(char *msg)
{
	char	**argv;
	char	*env;
	char	*exp_env;
	int		i;

	i = 0;
	argv = ft_split(msg, ' ');
	if (!argv)
		return (EXIT_FAILURE);
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '$')
		{
			env = ft_substr(argv[i], 1, ft_strlen(argv[i]) - 1);
			if (!env)
				return (EXIT_FAILURE);
			exp_env = getenv(env);
			if (exp_env)
				ft_printf("%s", exp_env);
			free(env);
		}
		else
			ft_printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	ft_free_matrix((void **)argv);
	return (EXIT_SUCCESS);
}

int	msh_echo(char *msg, int flag)
{
	if (msg[0] == '"')
	{
		if (echoWithQuotes(msg) == 1)
		{
			perror("echo");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (echoNoQuotes(msg) == 1)
		{
			perror("echo");
			return (EXIT_FAILURE);
		}
	}
	if (flag == 0)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}

/*void msh_exit(int t)
{
	// aqui se liberará la memoria que haga falta y se terminaran todos los procesos.
	ft_printf("exit\n");
	exit(t);
}*/