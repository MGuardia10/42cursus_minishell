/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:01:30 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/09 11:35:56 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `update_pwd` updates the value of the "PWD" environment variable
 * with the current working directory path.
 * 
 * @param envi The `envi` parameter in the `update_pwd` function is a
 * linked list structure containing environment variables.
 * 
 * @return The function `update_pwd` is returning an integer value. If the
 * function is successful, it will return 0. If there are any errors or failures
 * during the execution of the function, it will return 1.
 */
int	update_pwd(t_env_list *envi)
{
	char		pwd[PATH_MAX];
	char		*new_pwd;
	t_env_list	*aux;

	if (!already_exists(&envi, "PWD"))
		return (0);
	if (!getcwd(pwd, PATH_MAX))
		return (1);
	new_pwd = ft_strjoin("=", pwd);
	if (!new_pwd)
		return (1);
	aux = envi;
	while (aux)
	{
		if (ft_strcmp(aux->content->key, "PWD") == 0)
		{
			if (overwrite_env(&envi, aux->content->key, new_pwd))
				return (free(new_pwd), 1);
			return (free(new_pwd), 0);
		}
		aux = aux->next;
	}
	return (0);
}

/**
 * The function `update_oldpwd` updates the value of the environment variable
 * "OLDPWD" with a new value.
 * 
 * @param old_pwd The `update_oldpwd` function takes in the current working
 * directory path as `old_pwd`.
 * @param envi The `envi` parameter in the `update_oldpwd` function is a
 * linked list structure containing environment variables.
 * 
 * @return an integer value. If the operation is successful, it returns 0. 
 * If there are any errors during the process, it returns 1.
 */
int	update_oldpwd(char *old_pwd, t_env_list *envi)
{
	t_env_list	*aux;
	char		*new_old_pwd;

	if (!already_exists(&envi, "OLDPWD"))
		return (0);
	new_old_pwd = ft_strjoin("=", old_pwd);
	if (!new_old_pwd)
		return (1);
	aux = envi;
	while (aux)
	{
		if (ft_strcmp(aux->content->key, "OLDPWD") == 0)
		{
			if (overwrite_env(&envi, aux->content->key, new_old_pwd))
				return (free(new_old_pwd), 1);
			return (free(new_old_pwd), 0);
		}
		aux = aux->next;
	}
	return (0);
}

/**
 * The function `initialize_oldpwd` initializes the environment variable OLDPWD
 * if it does not already exist.
 * 
 * @param envi `envi` is a pointer to a linked list structure `t_env_list` that
 * contains environment variables.
 * 
 * @return an integer value. It returns 0 if the environment variable "OLDPWD"
 * already exists or it´s successfully created and 1 if there was any issue
 * setting the content or creating the variable.
 */
int	initialize_oldpwd(t_env_list **envi)
{
	t_env		*node_content;

	if (already_exists(envi, "OLDPWD"))
		return (0);
	node_content = set_env_content("OLDPWD");
	if (!node_content)
		return (1);
	if (create_new_env(envi, node_content))
		return (free_env(node_content), 1);
	return (0);
}
