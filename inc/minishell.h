/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/02 17:54:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBFT
*	unistd.h -> write, access, read, close, getcwd , chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot, 
*	fcntl.h  -> open (permisos)
*	stdlib.h -> malloc, free, exit, getenv
*	stdio.h  -> printf, perror
*/
#include "../libft/inc/libft.h"
#include <readline/readline.h>	// readline & co
#include <readline/history.h>
#include <sys/wait.h>			// wait, waitpid, wait3, wait4
#include <sys/stat.h>			// stat, lstat, fstat
#include <sys/types.h>			// opendir, readdir, closedir
#include <dirent.h>				// opendir, readdir, closedir
#include <sys/ioctl.h>			// ioctl
#include <termios.h>			// tcsetattr, tcgetattr
#include <curses.h>				// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <term.h>				// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <signal.h>				// signal, sigaction, kill
#include <string.h>				// strerror
#include <errno.h>				// para manejar errores

#endif