/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/20 19:28:35 by raalonso         ###   ########.fr       */
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
#include "../libft/inc/colors.h"
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

/*
*	Typedefs
*/
typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_env_list	t_env_list;
typedef struct s_line_p		t_line_p;
typedef struct s_command	t_command;
typedef struct s_cmd_list	t_cmd_list;

/*
*	Structs
*/
// env nodes
struct s_env
{
	char	*key;		// siempre existe una key, lo que puede no existir es un value "hola=" es permitido.
	char	*value;
};

struct	s_env_list
{
	t_env		*content;
	t_env_list	*next;
};

// command struct
struct s_command 
{
	char	*exe; // ejecutable (Ej: ls, cd, echo, etc)
	char	**args; // array de argumentos (incluye tmb las flags)
	int		redir; // tipo de redirección, ('|', '>', '>>', '<'), si no tiene -1.
};

struct s_cmd_list
{
	t_command	*content;
	t_cmd_list	*next;
};

// line parsed nodes
struct s_line_p
{
	char		*content;
	t_line_p	*next;
};

// general struct
struct	s_shell
{
	char		*line_read;
	t_env_list	*envi;
	t_line_p	*string_list;
	t_cmd_list	*cmds;
};

/*
*	ENV
*/
int		create_env_list(t_shell *shell, char **env);
t_env	*set_env_content(char *env_str);
int		create_new_env(t_env_list **envi, t_env *node_content);

/*
*	BUILTINS
*/
int		ft_env(t_env_list **envi, t_line_p *args);
int		ft_export(t_env_list **envi, t_line_p *args);
int		print_export(t_env_list **envi);
int		ft_unset(t_env_list **envi, t_line_p *args);
int		msh_pwd(void);
int		msh_cd(char *cmd);
int		msh_echo(char *msg, int flag);

/*
*	PARSE
*/
int		init_line(t_shell *shell);
int		check_quotes(t_shell *shell);
int		expand_line(t_shell *shell);

/*
*	UTILS
*/
void	free_env(void *content);
bool	already_exists(t_env_list **envi, char *key);
int		isdelimiter(char c);


#endif