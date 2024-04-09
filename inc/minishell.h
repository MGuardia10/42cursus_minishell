/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:01:57 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/09 11:37:56 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>

# define TEMP_PATH	"/tmp/msh-"

extern volatile sig_atomic_t	g_signal_status;

/******************************************************************************
*	Typedefs
******************************************************************************/
typedef struct s_shell			t_shell;
typedef struct s_env			t_env;
typedef struct s_env_list		t_env_list;
typedef struct s_command		t_command;
typedef struct s_io_files		t_io_files;

typedef enum e_redir			t_redir;
typedef enum e_sig_mode			t_sig_mode;

/******************************************************************************
*	Enums
******************************************************************************/
enum	e_redir
{
	NONE,
	PIPE,
	IN,
	OUT,
	APPOUT,
	HEREDOC
};

enum	e_sig_mode
{
	INTERACTIVE = 0,
	SIGINT_HD = 1,
	SIGINT_FATHER = 2,
	SIGINT_CHILD = 130,
	SIGQUIT_CHILD = 131
};

/******************************************************************************
*	Structs
******************************************************************************/
struct s_env
{
	char		*key;
	char		*value;
};

struct	s_env_list
{
	t_env		*content;
	t_env_list	*next;
};

struct	s_io_files
{
	t_redir		redir;
	char		*filename;
	char		*path;
	bool		expheredoc;
};

struct s_command
{
	char		*exe;
	char		**args;
	int			args_count;
	t_io_files	*infiles;
	int			infile_count;
	t_io_files	*outfiles;
	int			outfile_count;
};

struct	s_shell
{
	char		*line_read;
	t_env_list	*envi;
	t_command	*cmds;
	int			n_cmds;
	char		*home;
	int			stdin_dup;
	int			stdout_dup;
	int			infile_dup;
	int			outfile_dup;
	pid_t		last_pid;
	int			exit_status;
};

/******************************************************************************
*	FUNCTION PROTOTYPES
******************************************************************************/
/* SHELL */
int		init_shell(t_shell *shell, int argc, char **argv, char **env);
void	manage_input(t_shell *shell);
int		manage_exit_status(int status);
void	reset_shell(t_shell *shell);
void	free_infiles(t_command *cmd);
void	free_outfiles(t_command *cmd);
void	free_args(t_command *cmd);
void	free_cmds(t_shell *shell);
void	free_shell(t_shell *shell);

/* ENV */
int		create_env_list(t_shell *shell, char **env);
t_env	*set_env_content(char *env_str);
int		create_new_env(t_env_list **envi, t_env *node_content);
int		overwrite_env(t_env_list **envi, char *key, char *value);
int		set_home(t_shell *shell);
int		initialize_oldpwd(t_env_list **envi);
int		update_oldpwd(char *old_pwd, t_env_list *envi);
int		update_pwd(t_env_list *envi);
int		set_shlvl(t_env_list **envi);
int		verify_no_env_cases(t_env_list **envi);

/* BUILTINS */
int		ft_env(t_env_list **envi, char *arg);
int		ft_export(t_shell *shell, t_env_list **envi, char **args);
int		ft_unset(t_env_list **envi, char **args);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell, t_env_list *envi, char *arg);
int		ft_echo(char **args);
int		ft_exit(t_shell *shell, char **args, int args_count);

/* EXECUTER */
int		executer(t_shell *shell);
int		handle_builtins(t_shell *shell, t_command *cmd);
int		exec_builtin(t_shell *shell, char *cmd, char **args, int args_count);
int		handle_simple_commmands(t_shell *shell, t_command *cmd);
char	*find_path(t_shell *shell, char *cmd, t_env_list *envi, int *status);
int		manage_infiles(t_io_files *infiles, int in_count, int pipe);
int		manage_outfiles(t_io_files *outfiles, int out_count, int pipe);
int		resolve_heredocs(t_shell *shell, t_command *cmds, int n_cmds);
char	*create_temp_file(t_shell *shell);
int		check_access_tmp_folder(char *tmp_path);
void	create_child(t_shell *shell, int *fd1, int *fd2, int i);
int		wait_all_childs(int last_pid);

/* SIGNALS */
void	signal_handler(sig_t sigint_func, sig_t sigquit_func);
void	ft_sigint(int signal);
void	ft_sigint_heredoc(int signal);
void	ft_sigint_child(int signal);
void	ft_sigquit(int signal);
void	write_signals(t_shell *shell, bool write_signal);

/* PARSE */
int		init_line(t_shell *shell);
int		expand_line(t_shell *shell);
int		num_of_tokens(char *line);
char	**get_tokens(char *line);
int		handle_special_char(char *line, char **tokens, int *i, int *j);
void	store_tokens(char **tokens, t_shell *shell);
int		init_for_store(char **tokens, t_shell *shell);
int		clean_line(t_shell *shell, char **exp, int i, int j);
int		check_inside_quotes(t_shell *shell, int i, int f);
int		join_line(t_shell *shell, char **exp, int i, int j);
int		join_expenv(char **exp, char *env);
char	*expenv(t_shell *shell, int *i, int f);
int		extract_from_line(t_shell *shell, char **exp, int i, int j);
char	*non_existent_env(int f);
int		count_cmd(char **tokens);
void	store_exe(char **tokens, t_shell *shell, int *i, int *j);
int		store_infile(t_command *cmd, char **tokens, int *i);
int		store_outfile(t_command *cmd, char **tokens, int *i);
void	store_redir(char **tokens, t_shell *shell, int *i, int j);
void	store_arg(char **tokens, t_shell *shell, int i, int j);
int		unexpected_tokens(char **tokens);
int		check_quotes(char *line);
char	*check_next_quotes(char *line, char **tokens, int *i, int j);
int		move_iters(char *str, int *i, int *j);
int		isinvalidchar(char *str, int i);
void	change_quote(char **tokens, int j);
void	final_quote(char **token, int j);

/* UTILS */
void	free_env(void *content);
bool	already_exists(t_env_list **envi, char *key);
bool	isvalidchar(char c);
bool	is_builtin(char *cmd);
char	**envi_to_arr(t_env_list *env);
char	**create_argv(t_command cmd);
char	*ft_getenv(t_env_list *envi, char *key, int *flag);
bool	is_directory(const char *path);
void	clean_exit(t_shell *shell, int exit_code);
bool	is_special_char(char c);
t_redir	isredir(char *token);
bool	is_special_char_two(char c);
void	put_quotes(char **token, int j);

#endif