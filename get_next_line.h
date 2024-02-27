#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif

#include <stdlib.h>
#include <stdio.h>//
#include <fcntl.h>
#include <unistd.h>


char    *get_next_line(int fd);
int     ft_strlen(char *s);
void    ft_strjoin(char *dst, char *src, size_t n);
void    ft_strlcpy(char *dst, char *src, size_t n);



#endif