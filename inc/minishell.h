/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/07 22:22:43 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int		msh_pwd(void);
int		msh_cd(char *cmd);
void	msh_exit();
int		msh_echo(char *msg, int flag);

#endif