/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:59:57 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 02:57:16 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum token_type
{
	WORD,
	QUOTE,
	REDIRECTION,
	PIPE,
	SPACE_,
	VAR,
	R_REDIRECTION,
	L_REDIRECTION,
	A_REDIRECTION,
	H_REDIRECTION,
	FIRST_S,
	SECOND_S,
	FIRST_D,
	SECOND_D,
	EXEC_VAR,
}				t_token_type;

typedef struct s_lexer
{
	char			*data;
	int				type;
	int				index;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_cmds
{
	t_lexer			*cmd_nd_args;
	t_lexer			*rdrxs;
	char			**cmd;
	char			**rdrxs_array;
	int				in_fd;
	int				out_fd;
	int				herdoc_fd;
	struct s_cmds	*next;
}					t_cmds;

typedef struct env
{
	char			*env_var;
	int				env_or_export;
	struct env		*prev;
	struct env		*next;
}					t_env;

void				init(int ac, char **env, int **std_io, t_env **env_lst);

/*_________heredoc signal handler __________*/

void				exit_heredoc(int sig_num);
void				setup_signal_handlers(void);
void				close_and_restore_signals(int herdoc_fd);

/*_________________signals_________________*/

void				signals(void);

/*______________parse______________________*/

void				free_lexer(t_lexer **mi);
t_cmds				**splited_cmds(t_lexer **mi);
t_cmds				**parser(t_lexer **mi, t_env **env);
void				ft_rdrxadd_back(t_lexer **lst, t_lexer *new);
int					type_is_redirection(int type);
char				*syntaxe_error(t_lexer **mi);
unsigned int		cmds_nbr(t_lexer **mi);
t_lexer				*lexer_last(t_lexer **ptr);
int					ft_lstsize(t_lexer *lst);
void				cmd_inlexer_toarray(t_cmds **cmds);

/*_______________signal functions________________*/

void				sig_handler(int sig);

/*______________redirections_________________*/
char				*redirect(t_cmds **cmds);

/*____________env functions_________________*/

t_env				*set_env(char **envp);
t_env				*ft_envnew(char *content);
int					ft_envsize(t_env *lst);
void				ft_envadd_back(t_env **lst, t_env *new);
char				*get_envvar(t_env **env, char *str);
char				**envlist_toarray(t_env **env);

/*________________BUILTIN CMDS_____________*/

int					is_assigned(char *arg);
void				update_env(t_env *tmp, char *arg);
void				export_to_env(t_env **env, char *arg, int var_len);
void				_echo(char **args);
void				_cd(t_env **env, char *arg);
void				_pwd(void);
void				_env(t_env **env);
void				_unset(t_env **env, char **args);
void				ft_exit(char **args, int flag);
void				_export(t_env **env, char **args, int flag);

/*_________________execute fcts(iglezimn)_____________*/

int					here_doc(char *deli, t_env **env);
void				execute(char *cmd, char **cmd_args, char **env);
void				cmd_execute(t_cmds **multi_cmds, t_env **env);
void				single_cmd_execute(char *cmd, char **cmd_args, t_env **env);
int					a_builtin_cmd(char *cmd, char **args, t_env **env,
						int flag);
char				*get_cmd_path(char *cmd, t_env **env);
char				**envlist_toarray(t_env **env);
char				*get_cmd_path(char *cmd, t_env **env);
char				*get_abs_cmd(char *cmd, char *path);

/*________________talfunctionet tabalist_______________*/

void				error(char *err_msg, int exit_int);

/*___________________tabaqa lkadi7a____________________*/

int					ft_open(char *filenam, int oflag, mode_t mode);
int					is_directory(char *path);
void				ft_dup2(int newfd, int oldfd);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
long				ft_atoi(char *str);
void				ft_close(int fd);
int					ft_isdigit(int c);
char				*ft_strchr(char *s, int c);
int					ft_fork(void);
void				ft_pipe(int pipefds[]);
size_t				ft_max(size_t a, size_t b);
void				*ft_malloc(size_t size);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char *s, unsigned int start, size_t len);
int					ft_strsnbr(char *s, char c, int para, int mode);
void				*ft_memcpy(void *dst, void *src, size_t n);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strjoin(char *s1, char *s2);
void				ft_putstr_fd(char *s, int fd);
int					ft_strcmp(char *s1, char *s2);
char				**ft_split(char *s, char c);
void				ft_bzero(void *s, size_t n);
int					valid_argument(char *arg);
char				*ft_strdup(char *s1);
size_t				ft_strlen(char *s);
char				*ft_itoa(int n);
char				*sdup(char *s1);

/*_____________Parse functions______________________*/

void				ft_init_vars(t_lexer **h, int *array, int size);
t_lexer				**label_expand(t_lexer **lst);
t_lexer				*lexer(char *cmd, t_env **env);
t_lexer				*lexer_new(char *data, int index, int type);
void				lexer_add_back(t_lexer **head, t_lexer *new);
void				process_word(char *cmd, int *c, t_lexer **head);
void				process_right_redirection(char *cmd, int *c,
						t_lexer **head);
void				process_left_redirection(char *cmd, int *c, t_lexer **head);
void				process_pipe(char *cmd, int *c, t_lexer **head);
void				process_quote(char *cmd, int *c, t_lexer **head);
void				process_single_quote(char *cmd, int *c, t_lexer **head);
void				process_double_quote(char *cmd, int *c, t_lexer **head);
void				process_var(char *cmd, int *c, t_lexer **head);
void				pop_node(t_lexer **head, t_lexer *node);
void				remove_unwanted(t_lexer **head);
char				*get_var_from_env(char *var);
t_lexer				**expander(t_lexer **head, t_env **env);
t_lexer				**del_unwanted(t_lexer **lst);
t_lexer				**merge_words(t_lexer **head);
t_lexer				*fix_index(t_lexer **head);

/*__________________free the memory_____________________*/

void				free_cmds(t_cmds **cmds);
void				free_envirenment(t_env *env_lst);

extern int			g_exit_status;

#endif