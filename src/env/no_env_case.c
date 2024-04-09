/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:38:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/09 11:35:16 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function creates a new environment variable for the current working
 * directory in a shell structure.
 * 
 * @param shell The `shell` parameter is a pointer to a structure of type
 * `t_shell`.
 * @param pwd The `pwd` parameter in the `create_pwd` function is a pointer to a
 * character array that represents the current working directory path.
 * 
 * @return If the function executes successfully, it returns 0. If there is an
 * error during execution, it returns 1.
 */
static int	create_pwd(t_env_list **envi, char *pwd)
{
	char		*pwd_str;
	t_env		*pwd_node;

	if (already_exists(envi, "PWD"))
		return (0);
	pwd_str = ft_strjoin("PWD=", pwd);
	if (!pwd_str)
		return (1);
	pwd_node = set_env_content(pwd_str);
	free(pwd_str);
	if (!pwd_node)
		return (1);
	if (create_new_env(envi, pwd_node))
		return (free_env(pwd_node), 1);
	return (0);
}

/**
 * The function creates a new environment variable "_" with the value of the
 * current shell.
 * 
 * @param shell The `shell` parameter is a pointer to a structure of type
 * `t_shell`. 
 * @param pwd The `pwd` parameter represent the current working directory path.
 * 
 * @return If the function executes successfully, it returns 0. If there is an
 * error during execution, it returns 1.
 */
static int	create_underscore(t_env_list **envi, char *pwd)
{
	char		*underscore_str1;
	char		*underscore_str2;
	t_env		*underscore_node;

	if (already_exists(envi, "_"))
		return (0);
	underscore_str1 = ft_strjoin(pwd, "/./minishell");
	if (!underscore_str1)
		return (1);
	underscore_str2 = ft_strjoin("_=", underscore_str1);
	free(underscore_str1);
	if (!underscore_str2)
		return (1);
	underscore_node = set_env_content(underscore_str2);
	free(underscore_str2);
	if (!underscore_node)
		return (1);
	if (create_new_env(envi, underscore_node))
		return (free_env(underscore_node), 1);
	return (0);
}

/**
 * The function `no_env_case` sets the current working directory and "_" 
 * variable accordingly.
 * 
 * @param shell The `shell` parameter is a pointer to a structure of type
 * `t_shell`.
 * 
 * @return If the function executes successfully, it returns 0. If there is an
 * error during execution, it returns 1.
 */
int	verify_no_env_cases(t_env_list **envi)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (perror("getcwd"), 1);
	if (create_pwd(envi, pwd))
		return (perror("malloc"), 1);
	if (create_underscore(envi, pwd))
		return (perror("malloc"), 1);
	if (initialize_oldpwd(envi))
		return (perror("malloc"), 1);
	if (set_shlvl(envi))
		return (perror("malloc"), 1);
	return (0);
}
