/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:46:54 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/09 11:00:16 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function ft_cd_home changes the current directory to the HOME directory
 * specified in the environment variables.
 * 
 * @param envi A pointer to a structure that holds environment variables and 
 * their values.
 * @param curr_dir The `curr_dir` parameter is a string that represents the
 * current directory path.
 * @param flag The `flag` parameter in the `ft_cd_home` function is used to
 * indicate whether the HOME environment variable is set or not. If `flag` is 1,
 * it means HOME is not set, and an error message specific to that scenario is
 * displayed. Otherwise, a general error message is set.
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
 * @param home The `home` parameter in the `ft_cd_initial_dir` function likely
 * represents the home directory path of the user. It is used as a fallback
 * option in case changing the directory to the HOME variable path fails.
 * @param curr_dir The `curr_dir` parameter represents the current directory.
 * @param flag The `flag` parameter is used to indicate whether the `HOME`
 * environment variable is successfully retrieved.
 * 
 * @return The function `ft_cd_initial_dir` returns an integer value. If the
 * function executes successfully, it returns 0. If there is an error during the
 * execution, it returns 1.
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
 * The function `ft_cd_minus` changes the current directory to the previous
 * directory stored in the environment variable "OLDPWD".
 * 
 * @param envi The `envi` parameter is a list that contains environment
 * variables. In this context, it is being used to retrieve the value of the
 * "OLDPWD" environment variable.
 * @param curr_dir The `curr_dir` parameter represents the current directory.
 * @param flag The `flag` parameter is a pointer to an integer. It is used to
 * indicate whether a specific condition is met during the execution of the 
 * function. In this case, it is used to check if "OLDPWD" is set or not.
 * 
 * @return The function `ft_cd_minus` is returning an integer value. If the
 * function executes successfully, it returns 0. If there is an error during the
 * execution, it returns 1.
 */
int ft_cd_minus(t_env_list *envi, char *curr_dir, int *flag)
{
	char	*oldpwd;

	oldpwd = ft_getenv(envi, "OLDPWD", flag);
	if (chdir(oldpwd) != 0)
	{
		if (*flag == 1)
			ft_fprintf(2, "minishell: cd: OLDPWD not set\n");
		else
			perror("minishell: cd");
		return (1);
	}
	printf("%s\n", oldpwd);
	if (update_oldpwd(curr_dir, envi) || update_pwd(envi))
		return (perror("minishell"), 1);
	return (0);
}

/**
 * The function `ft_cd_dir` changes the current directory and updates the
 * environment variables accordingly.
 * 
 * @param arg The `arg` parameter in the `ft_cd_dir` function is a string which
 * represents the directory path that the user wants to change to.
 * @param envi The `envi` parameter is a linked list. It is used to access and
 * update environment variables related to the current shell session.
 * @param curr_dir `curr_dir` is a string that stores the actual directory path.
 * 
 * @return The function `ft_cd_dir` returns an integer value. If the `chdir`
 * function fails (returns a non-zero value), it prints an error message using
 * `ft_fprintf`, sets the error message using `perror`, and returns 1. If the
 * updates to the oldpwd or pwd fail, it prints an error message and returns 1.
 * Otherwise, it returns 0.
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
 * including special cases "cd", "cd """, "cd ~" and "cd -".
 * 
 * @param envi The `envi` parameter is a pointer to a structure or list that
 * contains environment variables. It is used in the `ft_cd` function to access
 * environment information such as the current directory and home directory.
 * @param home The `home` parameter in the `ft_cd` function represents the
 * home directory of the user.
 * @param arg The `arg` parameter represents the argument passed to the `cd` 
 * command. It is used to determine the directory to change to.
 * 
 * @return The function `ft_cd` is returning an integer value. Returns 0 when
 * the directory is changed correctly and 1 if there was an error.
 */
int	ft_cd(t_env_list *envi, char *home, char *arg)
{
	char	curr_dir[PATH_MAX];
	int	flag;

	if (!getcwd(curr_dir, PATH_MAX))
		return (perror("minishell: "), 1);
	flag = 0;
	if (!arg || arg[0] == '\0')
		return (ft_cd_home(envi, curr_dir, &flag));
	else if (ft_strcmp(arg, "\"\"") == 0)
		return (0);
	else if (ft_strcmp(arg, "~") == 0)
		return (ft_cd_initial_dir(envi, home, curr_dir, &flag));
	else if(ft_strcmp(arg, "-") == 0)
		return (ft_cd_minus(envi, curr_dir, &flag));
	else
		return (ft_cd_dir(arg, envi, curr_dir));
	return (0);
}
