/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:46:58 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/14 09:36:24 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the value of an environment variable when the input message is
 * surrounded by quotes.
 * 
 * @param msg The input message containing the environment variable.
 * @param i A pointer to the current index in the message.
 * @return 0 if successful, 1 if memory allocation fails.
 */
int	print_env_quotes(char *msg, int *i)
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
		return (1);
	exp_env = getenv(env);
	if (exp_env)
		ft_printf("%s", exp_env);
	free(env);
	return (0);
}

/**
 * Prints the value of an environment variable when the input message is not
 * surrounded by quotes.
 * 
 * @param argv An array of command-line arguments.
 * @param i The index of the argument containing the environment variable.
 * @return Returns 0 on success, 1 on failure.
 */
int	print_env_no_quotes(char **argv, int i)
{
	char	*env;
	char	*exp_env;

	env = ft_substr(argv[i], 1, ft_strlen(argv[i]) - 1);
	if (!env)
		return (1);
	exp_env = getenv(env);
	if (exp_env)
		ft_printf("%s", exp_env);
	free(env);
	return (0);
}

/**
 * Prints the message when the message is surrounded by quotes,
 * handling environment variables.
 * 
 * @param msg The message to be printed.
 * @return 1 if an error occurred, 0 otherwise.
 */
int	echo_with_quotes(char *msg)
{
	int	i;

	i = 1;
	while (msg[i] != '\0' && msg[i] != '"')
	{
		if (msg[i] == '$')
		{
			if (print_env_quotes(msg, &i) == 1)
				return (1);
		}
		ft_printf("%c", msg[i]);
		i++;
	}
	return (0);
}

/**
 * Prints the message when the message is not surrounded by quotes,
 * handling environment variables.
 * 
 * @param msg The message to be printed.
 * @return 1 if an error occurred, 0 otherwise.
 */
int	echo_no_quotes(char *msg)
{
	char	**argv;
	int		i;

	i = 0;
	argv = ft_split(msg, ' ');
	if (!argv)
		return (1);
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '$')
		{
			if (print_env_no_quotes(argv, i) == 1)
				return (1);
		}
		else
			ft_printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	ft_free_matrix((void **)argv);
	return (0);
}

/**
 * Executes the echo command with the given message and flag.
 * If the message is introduced with quotes, it calls echo_with_quotes function.
 * If the message is not introduced with quotes, it calls echo_no_quotes
 * function.
 * If any of the echo functions return an error, it prints an error message and
 * returns 1.
 * If the flag is 0 (-n is not introduced), it prints a newline character after
 * executing the echo command.
 *
 * @param msg The message to be echoed.
 * @param flag The flag indicating whether to print a newline character or not.
 * @return 0 if the echo command is executed successfully, 1 otherwise.
 */
int	msh_echo(char *msg, int flag)
{
	if (msg[0] == '"')
	{
		if (echo_with_quotes(msg) == 1)
		{
			perror("echo");
			return (1);
		}
	}
	else
	{
		if (echo_no_quotes(msg) == 1)
		{
			perror("echo");
			return (1);
		}
	}
	if (flag == 0)
		ft_printf("\n");
	return (0);
}
