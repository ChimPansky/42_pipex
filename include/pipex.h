/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:03:28 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/01 22:10:47 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <wait.h>
# include <fcntl.h>

# define ERR_MALLOC "Memory Allocation Error"
# define ERR_TOO_FEW_ARGS "Not enough arguments"
# define ERR_TOO_MANY_ARGS "Too many arguments"
# define ERR_PIPE_FDS "Could not create FDs for piping"
# define ERR_CREATE_PIPES "Could not create pipe(s)"
# define ERR_CLOSE_FD "Error closing FD"
# define ERR_FD_DUP "Error duplicating FD"
# define ERR_DEAD_CHILD "Child died during birth :("
# define ERR_UNKOWN "Unknown Error"

typedef struct s_pipex
{
	int		pipe_count;
	int		child_no;
	pid_t	child_pid;
	int		*pipe_fds;
	int		*closed_pipe_fds;
	int		infile_fd;
	int		outfile_fd;
	int		logfile_fd;
	char	**bin_paths;
	char	*cmd_path;
	char	**cmd_argv;

}				t_pipex;

// pipex.c
int		main(int argc, char *argv[], char *envp[]);
void	px_child_labor(t_pipex *px, char *args);

// px_utils.c
void	px_dup2(t_pipex *px, int old_fd, int new_fd);
void	px_set_nulls(t_pipex *px);
void	px_init(t_pipex *px, int argc, char *argv[], char *envp[]);
void	px_destroy(t_pipex *px);

// px_file_descriptors.c
int		*ft_create_pipe_fds(t_pipex *px);
void	ft_create_pipes(t_pipex *px);
void	px_close_fd(t_pipex *px, int fd);
void	ft_close_child_fds(t_pipex *px);
void	ft_close_parent_fds(t_pipex *px);

// px_commands.c
char	**ft_get_bin_paths(char *envp[]);
char	*ft_get_command_path(t_pipex *px, char *command);
void	px_set_command(t_pipex *px, char *args);

// px_error_handling.c
void	px_error(char *err_msg);
void	px_exit(t_pipex *px);
void	px_error_exit(t_pipex *px, char *err_msg);

// px_logging.c
void	px_create_logfile(t_pipex *px);
void	ft_print_pipe_fds(t_pipex *px, int *fds);

#endif
