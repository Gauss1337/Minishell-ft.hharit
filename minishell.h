/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 22:44:04 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 08:47:49 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include "get_next_line/get_next_line.h"

# define EXEC 1 
# define PIPE 2
# define REDIR 3
# define HEREDOC 4

typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	char	*args[1024];
	int		argc;
	t_cmd	*cmd;
}	t_exec;

typedef struct s_pipe
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_pipe;

typedef struct s_redir
{
	int		type;
	char	*file;
	t_cmd	*cmd;
	int		open_file;
	int		fd;
	int		flags;
}	t_redir;

typedef struct l_par
{
	pid_t	id;
	pid_t	f;
	int		child;
	char	*ptr;
	char	*str;
	int		exit;
	int		exit_status;
	int		p[2];
}	t_par;

typedef struct s_heredoc
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		open_file;
	int		fd;
	char	*temp;
	char	*line;
	int		flags;
	char	*delim;
}	t_heredoc;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct t_glob
{
	int	errors;
	int	exit;
}	t_glob;

typedef struct s_doc
{
	char	*temp;
	char	*line;
	pid_t	pid;
	int		exits;
}	t_doc;

void		signals3(void);
void		free_exec(t_cmd *cmd);
int			ft_strcmp(char *s1, char *s2);
void		signals(void);
void		free_args(char **str);
void		sig_handl(int sig);
void		signals2(void);
void		sig_handle(int sig);
void		heredoc_signal(void);
void		ctrl_handler(int sig);
int			get_exits(int exit_status);
char		**ft_split(char const *str, char c);
int			check_sep(char *sep, char c);
int			check_symbol(char *str, char *stre, char *symbol);
size_t		ft_strlen(const char *str);
char		*ft_strrchr(const char *str, int c);
char		*ft_strchr(const char *s, int c);
int			get_token(char **str, char *end_str, char **previous, char **ep);
int			check_append(char **ptr);
int			check_herdoc(char **ptr);
void		check_builtin(t_exec *ecmd, char **env, t_list **env_l, int built);
int			token(char **ptr, char *stre, int tok);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(const char *s1);
t_cmd		*parse_exec(char **str, char *stre, t_list *env_l);
t_cmd		*get_cmd(void);
t_cmd		*parse_redirs(t_cmd *cmd, char **str, char *stre, t_list *env_l);
char		*ret_str(char *str, char *stre);
int			is_symbol(char *str, char *stre, char *symbol);
t_cmd		*pipe_data(t_cmd *right, t_cmd *left);
t_redir		*redir_data(char *file, int flags, int fd, t_list *env_l);
t_cmd		*parse_pipe(char **str, char *stre, t_list *env_l);
int			redir_error(int tok);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void	*s, size_t	n);
void		runcmd(t_cmd *cmd, char **env, int built, t_list **env_l);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_isalpha(int c);
int			special_char(char c);
void		here_doc(t_cmd *cmd);
char		*ft_strjoin4(char *s1, char *s2);
t_heredoc	*heredoc_data(char *file, int flags, int fd);
void		fail(char *str);
char		*comd(char **envp, t_exec *list);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strjoin(const char *s1, char *s2);
void		ft_putchar_fd(char c, int fd);
void		check_file(t_redir *rcmd);
t_cmd		*handle_redir(t_redir *rcmd, int fd);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			pipe_exit(int exits);
void		ft_pipe(t_cmd *cmd, char **env, int built, t_list **env_l);
void		check_redir(t_redir *rcmd);
t_cmd		*here(t_heredoc *hd);
char		*quotes(char *str, t_list *env_l);
void		skip_quotes(char **ptr, char *stre);
char		*fct(char **str, char quote);
char		*ft_strjoin5(char *s1, char *s2);
int			ft_atoi(const char *str);
void		cmd_error(char *str);
void		exec(t_exec *ecmd, char **env, t_list **env_l, int built);
void		dollar(char **str, char **new_str, char **rest, t_list *env_l);
int			is_variable(char c);
char		*var_dollar(char *str, t_list *env_l);
char		*ret_dollar(char *str);
char		*ft_itoa(int n);
char		*str_quotes(char **str, char symbol, t_list *env_l);
char		*stop(char **str, char symbol);
char		*str_dollar(char **str, t_list *env_l);
char		*verify(char *str, t_list *env_l);
char		*quotes_dollar(char *str, t_list *env_l);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
char		*ft_strjoin6(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		pwd(void);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		display_env(t_list *list);
void		cd(const char *str);
void		echo(char **str);
void		ft_exit(char **list);
size_t		ft_strlen(const char *str);
void		export(t_list **list, char **str);
t_list		*env(t_list *list, char **envt);
t_list		*ft_lstnew(void *content);
void		unset(t_list **list, char **str, char **envp);
void		exec_b(t_exec *exec, char **env, t_list **env_l);
void		ft_run_here(t_cmd *cmd, char **env, int built, t_list **env_l);
void		exit_handle(int exits);
int			valid_string(char *str, char *cmd);
char		*ret_exp(char *str);
int			check_syntax(char *check);
void		export_only(t_list	*env);
char		*get_right_name(char	*str);
t_cmd		*exec_builtin(t_cmd *cmd, char **envp, t_list **env_l, int *child);
void		check_cmd(char *cmd, int c);
void		free_cmd(t_cmd *cmd);
int			check_errors(t_cmd *cmd);
void		check_dir(char *str);
void		is_dir(char *str, DIR *dir, int exit_value);
void		not_f_dir(char *str, int exit_value);
void		perm_denied(char *str, int exit_value);
void		check_free(char *str);
void		rest(char *str, char *stre, char **new, char *join);
char		*quotes_dollar(char *str, t_list *env_l);
char		which_symbol(char *str, char *stre);
char		*something(char **str, char symbol, t_list *env_l);
int			ft_lstsize(t_list *lst);
#endif
