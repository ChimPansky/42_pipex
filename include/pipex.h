#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>

# include <string.h>	// for strncmp -> delete later and replace with ft_strncmp

# define ERR_MALLOC "Memory Allocation Error"
# define ERR_UNKOWN "Unknown Error"

// Colors
# define COLOR_RESET "\033[0;39m"
# define COLOR_RED "\033[0;91m"
# define COLOR_GREEN "\033[0;92m"
# define COLOR_YELLOW "\033[0;93m"

// typedef struct	s_char2_alloc
// {
// 	char					**content;
// 	struct s_char2_alloc 	*next;
// }				t_char2_alloc;
// typedef struct s_char1_allocs
// {
// 	char 					*content;
// 	struct s_char1_alloc	*next;
// }				t_char1_alloc;

// typedef struct s_pipex
// {
// 	t_char2_alloc	*char2_allocs;
// 	t_char1_alloc	*char1_allocs;
// }				t_pipex;

// void	px_init(t_pipex *px);

// void	px_add_char2_alloc(t_pipex *px, t_char2_alloc *char2);
// void	px_add_char1_alloc(t_pipex *px, t_char1_alloc *char1);
// error_handling.c
void	px_error_exit(char *err_msg);



#endif
