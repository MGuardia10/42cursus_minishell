/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/09 01:09:57 by mguardia         ###   ########.fr       */
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
typedef struct s_command	t_command;

/*
*	Structs
*/
// env nodes
struct s_env
{
	char	*key;
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

// general struct
struct	s_shell
{
	char		*line_read;
	t_env_list	*envi;
	t_command	*cmds; // array de comandos
	int			n_cmds; // numero de comandos
	char		*home;	// para cd ~
	int			exit_status;
};

/*
*	ENV
*/
int		create_env_list(t_shell *shell, char **env);
t_env	*set_env_content(char *env_str);
int		create_new_env(t_env_list **envi, t_env *node_content);
int		overwrite_env(t_env_list **envi, char *key, char *value);
int		set_home(t_shell *shell);
int		initialize_oldpwd(t_env_list *envi);
int		update_oldpwd(char *old_pwd, t_env_list *envi);
int		update_pwd(t_env_list *envi);

/*
*	BUILTINS
*/
int		ft_env(t_env_list **envi, char **args);
int		ft_export(t_env_list **envi, char **args);	
int		ft_unset(t_env_list **envi, char **args);
int		ft_pwd(void);
int		ft_cd(t_env_list *envi, char *home, char *args);
int		ft_echo(char **args);
int		ft_exit(t_shell *shell);
// int		ft_echo(char *msg, int flag);

/*
*	PARSE
*/
int		init_line(t_shell *shell);
int		check_quotes(t_shell *shell);
int		expand_line(t_shell *shell);

/*
*	EXECUTER
*/
int		executer(t_shell *shell);
int		handle_builtins(t_shell *shell, char *cmd);
int		handle_simple_commmands(t_shell *shell);
char	*find_path(char *cmd, t_env_list *envi, int *status);

/*
*	UTILS
*/
void	free_env(void *content);
bool	already_exists(t_env_list **envi, char *key);
int		isdelimiter(char c);
bool	is_builtin(char *cmd);
char	**envi_to_arr(t_env_list *env);
char	**create_argv(t_command cmd);
char	*ft_getenv(t_env_list *envi, char *key, int *flag);
bool	is_directory(const char *path);

#endif