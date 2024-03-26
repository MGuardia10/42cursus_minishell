/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 18:45:25 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/colors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
// # include <sys/types.h>	// opendir, readdir, closedir
// # include <dirent.h>		// opendir, readdir, closedir
# include <sys/ioctl.h>
# include <termios.h>		// tcsetattr, tcgetattr
// # include <curses.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
// # include <term.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <signal.h>
# include <errno.h>

# define TEMP_PATH	"/tmp/msh-"

extern volatile sig_atomic_t	g_signal_status;

/*
*	Typedefs
*/
typedef struct s_shell			t_shell;
typedef struct s_env			t_env;
typedef struct s_env_list		t_env_list;
typedef struct s_command		t_command;
typedef struct s_io_files		t_io_files;

typedef enum e_redir			t_redir;
typedef enum e_sig_mode			t_sig_mode;

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

enum	e_sig_mode
{
	INTERACTIVE = 0,
	SIGINT_HD = 1,
	NON_INTERACTIVE = 2,
	SIGINT_FATHER = 3,
	SIGINT_CHILD = 130,
	SIGQUIT_CHILD = 131
};

/*
*	Structs
*/
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

	// last pid
	pid_t		last_pid;

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
int		ft_export(t_shell *shell, t_env_list **envi, char **args);
int		ft_unset(t_env_list **envi, char **args);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell, t_env_list *envi, char *arg);
int		ft_echo(char **args);
int		ft_exit(t_shell *shell, char **args);

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
int		handle_builtins(t_shell *shell, t_command *cmd);
int		exec_builtin(t_shell *shell, char *cmd, char **args);
int		handle_simple_commmands(t_shell *shell, t_command *cmd);
char	*find_path(t_shell *shell, char *cmd, t_env_list *envi, int *status);
int		manage_infiles(t_io_files *infiles, int in_count, int pipe);
int		manage_outfiles(t_io_files *outfiles, int out_count, int pipe);
int		resolve_heredocs(t_shell *shell, t_command *cmds, int n_cmds);
char	*create_temp_file(t_shell *shell);
int		check_access_tmp_folder(char *tmp_path);
void	create_child(t_shell *shell, int *fd1, int *fd2, int i);
int		wait_all_childs(int last_pid);

/*
*	SIGNALS
*/
void	signal_handler(sig_t sigint_func, sig_t sigquit_func);
void	ft_sigint(int signal);
void	ft_sigint_heredoc(int signal);
void	ft_sigint_child(int signal);
void	ft_sigquit(int signal);

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
void	remove_temp_files(t_command *cmds, int n_cmds);
void	clean_exit(t_shell *shell, int exit_code);

#endif