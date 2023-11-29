#ifndef PIPEX_H
# define PIPEX_H

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

// error_handling.c
void	px_error_exit(char *err_msg);



#endif
