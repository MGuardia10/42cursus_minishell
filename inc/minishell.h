/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/22 17:39:33 by mguardia         ###   ########.fr       */
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
# include "../libft/inc/libft.h"
# include "../libft/inc/colors.h"
# include <readline/readline.h>	// readline & co
# include <readline/history.h>
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <sys/stat.h>			// stat, lstat, fstat
# include <sys/types.h>			// opendir, readdir, closedir
# include <dirent.h>			// opendir, readdir, closedir
# include <sys/ioctl.h>			// ioctl
# include <termios.h>			// tcsetattr, tcgetattr
# include <curses.h>			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>				// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <signal.h>			// signal, sigaction, kill
# include <string.h>			// strerror
# include <errno.h>				// para manejar errores

# define TEMP_PATH	"/tmp/msh-"

/*
*	Typedefs
*/
typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_env_list	t_env_list;
typedef struct s_command	t_command;
typedef struct s_io_files	t_io_files;

typedef enum e_redir		t_redir;

/*
*	Enums
*/
enum	e_redir
{
	NONE,
	IN,
	OUT,
	APPOUT,
	HEREDOC
};

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

struct	s_io_files
{
	// tipo de redireccion
	t_redir	redir;

	// nombre del archivo o en heredoc delimitador
	char	*filename;

	// path al archivo temporal si es HEREDOC
	char	*path;

	// si expande o no el heredoc, en cado que redir == HEREDOC
	bool	expheredoc;
};

struct s_command
{
	// comando principal
	char		*exe;

	// flags y argumentos del comando
	char		**args;

	// infiles del comando
	t_io_files	*infiles;
	int			infile_count;

	// outfiles del comando
	t_io_files	*outfiles;
	int			outfile_count;
};

struct	s_shell
{
	// linea leída de STDIN
	char		*line_read;

	// environment linked list
	t_env_list	*envi;

	// Array de comandos y total de comandos
	t_command	*cmds;
	int			n_cmds;

	// home para cd ~
	char		*home;

	// stdin, stdout
	int			stdin_dup;
	int			stdout_dup;

	// last infile, outfile
	int			infile_dup;
	int			outfile_dup;

	// codigo de error del ultimo comando
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
int		set_shlvl(t_env_list *envi);

/*
*	BUILTINS
*/
int		ft_env(t_env_list **envi, char **args);
int		ft_export(t_env_list **envi, char **args);	
int		ft_unset(t_env_list **envi, char **args);
int		ft_pwd(void);
int		ft_cd(t_env_list *envi, char *home, char *args);
int		ft_echo(char **args);
int		ft_exit(t_shell *shell, char **args);
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
int		handle_builtins(t_shell *shell, t_command cmd, int fd_in, int fd_out);
int		handle_simple_commmands(t_shell *shell, int fd_in, int fd_out);
char	*find_path(char *cmd, t_env_list *envi, int *status);
int		manage_infiles(t_shell *shell, t_io_files *infiles, int in_count);
int		manage_outfiles(t_io_files *outfiles, int out_count);
int		resolve_heredoc(t_shell *shell, t_io_files *infiles, int i, int in_count);
char	*create_temp_file(void);
int		check_access_tmp_folder(char *tmp_path);
void	remove_temp_files(t_io_files *infiles, int in_count);

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