/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:46:54 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/24 18:21:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function ft_cd_home changes the current directory to the HOME directory
 * specified in the environment variables.
 * 
 * @param envi a pointer to a structure that holds environment variables and 
 * their values.
 * @param curr_dir a string that represents the current directory path.
 * @param flag a pointer to an integer that indicates whether the HOME
 * environment variable is set or not.
 * 
 * @return The function `ft_cd_home` returns an integer value. If the `chdir`
 * operation to the home directory is successful, it returns 0. If there is an
 * error during the `chdir` operation or updating the oldpwd or pwd fails, it
 * returns 1.
 */
int	ft_cd_home(t_env_list *envi, char *curr_dir, int *flag)
{
	if (chdir(ft_getenv(envi, "HOME", flag)) != 0)
	{
		if (*flag == 1)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			perror("minishell: cd");
		return (1);
	}
	if (update_oldpwd(curr_dir, envi) || update_pwd(envi))
		return (perror("minishell"), 1);
	return (0);
}

/**
 * The function `ft_cd_initial_dir` changes the current directory to the home
 * directory and updates environment variables accordingly.
 * 
 * @param envi The `envi` parameter seems to be a list that contains environment
 * variables.
 * @param home a string that represents the home directory path of the user.
 * @param curr_dir The `curr_dir` parameter represents the current directory.
 * @param flag The `flag` parameter is used to indicate whether the `HOME`
 * environment variable is successfully retrieved.
 * 
 * @return an integer value. If the function executes successfully, it
 * returns 0. If there is an error during the execution, it returns 1.
 */
int	ft_cd_initial_dir(t_env_list *envi, char *home, char *curr_dir, int *flag)
{
	if (chdir(ft_getenv(envi, "HOME", flag)) != 0)
	{
		if (*flag == 1)
		{
			if (chdir(home) != 0)
				return (perror("minishell: cd"), 1);
		}
		else
			return (perror("minishell: cd"), 1);
	}
	if (update_oldpwd(curr_dir, envi) || update_pwd(envi))
		return (perror("minishell"), 1);
	return (0);
}

/**
 * changes the current directory to the previous directory stored in the
 * environment variable "OLDPWD".
 * 
 * @param envi a linked list that contains environment variables.
 * @param curr_dir a string that represents the current directory.
 * @param flag a pointer to an integer.
 * 
 * @return an integer value. If the function executes successfully, it
 * returns 0. If there is an error during the execution, it returns 1.
 */
int	ft_cd_minus(t_env_list *envi, char *curr_dir, int *flag)
{
	char	*oldpwd;

	oldpwd = ft_getenv(envi, "OLDPWD", flag);
	if (chdir(oldpwd) != 0)
	{
		if (*flag == 1)
			ft_fprintf(2, "minishell: cd: OLDPWD not set\n");
		else
		{
			ft_fprintf(2, "minishell: cd: %s: ", oldpwd);
			perror("");
		}
		return (1);
	}
	printf("%s\n", oldpwd);
	if (update_oldpwd(curr_dir, envi) || update_pwd(envi))
		return (perror("minishell"), 1);
	return (0);
}

/**
 * changes the current directory and updates the environment variables
 * accordingly.
 * 
 * @param arg a string which represents the directory path that the user wants
 * to change to.
 * @param envi a linked list. It is used to access and update environment
 * variables related to the current shell session.
 * @param curr_dir a string that stores the actual directory path.
 * 
 * @return an integer value. If the `chdir` function fails (returns a non-zero
 * value), it prints an error messageand returns 1. If the updates to the oldpwd
 * or pwd fail, it prints an error message and returns 1. Otherwise, returns 0.
 */
int	ft_cd_dir(char *arg, t_env_list *envi, char *curr_dir)
{
	if (chdir(arg) != 0)
	{
		ft_fprintf(2, "minishell: cd: %s: ", arg);
		return (perror(NULL), 1);
	}
	if (update_oldpwd(curr_dir, envi) || update_pwd(envi))
		return (perror("minishell"), 1);
	return (0);
}

/**
 * The function `ft_cd` handles changing directories in a shell program,
 * including special cases "cd", "cd "\"\"", "cd ~" and "cd -".
 * 
 * @param envi a linked list that contains environment variables.
 * @param home a string that represents the home directory of the user.
 * @param arg a string that represents the argument passed to the `cd` 
 * command. It is used to determine the directory to change to.
 * 
 * @return an integer value. Returns 0 when the directory is changed correctly
 * and 1 if there was an error.
 */
int	ft_cd(t_env_list *envi, char *home, char *arg)
{
	char	curr_dir[PATH_MAX];
	int		flag;

	if (!getcwd(curr_dir, PATH_MAX))
		return (perror("minishell"), 1);
	flag = 0;
	if (!arg || arg[0] == '\0')
		return (ft_cd_home(envi, curr_dir, &flag));
	else if (ft_strcmp(arg, "\"\"") == 0)
		return (0);
	else if (ft_strcmp(arg, "~") == 0)
		return (ft_cd_initial_dir(envi, home, curr_dir, &flag));
	else if (ft_strcmp(arg, "-") == 0)
		return (ft_cd_minus(envi, curr_dir, &flag));
	else
		return (ft_cd_dir(arg, envi, curr_dir));
	return (0);
}
