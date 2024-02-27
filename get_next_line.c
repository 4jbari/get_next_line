#include "get_next_line.h"
int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}
//FREE() AND SET TO NULL 
void    ft_free(char **s)
{
        free(*s);
        *s = NULL;
}
//ft_join COPYING AND JOINING A STRING TO ANOTHER ONE 
char    *ft_join(char *s1, char *s2)
{
    char *re_line;
    int i;
    int j;

    i = 0;
    j = ft_strlen(s1) + ft_strlen(s2);
    re_line = malloc((j + 1) * sizeof(char));
    if (!re_line)
    {
        ft_free(&s1);
        // ft_free(&s2);
        return NULL;
    }
    while (s1 && s1[i])
    {
        re_line[i] = s1[i];
        i++; 
    }
    j = 0;
    while (s2 && s2[j])
        re_line[i++] = s2[j++];
    re_line[i] = '\0';
    free(s1);
    s1 = NULL;
    return (re_line);
}

char    *ft_re_line(char *line)
{
    char    *return_line;
    int     i;

    i = 0;
    while (line[i] && line[i] != '\n')
        i++;
    if (line[i] == '\n')
        i++;
    return_line = malloc((i + 1)* sizeof(char));
    if (!return_line)
        return NULL;
    i = 0;
    while(line[i] && line[i] != '\n')
    {
        return_line[i] = line[i];
        i++;
    }
    if (line[i] == '\n')
    {
        return_line[i] = line[i];
        i++;
    }
    return_line[i] = '\0';
    return(return_line);
}
char    *rest(char *line)
{
    char    *rest;
    int i;
    int j;

    i = 0;
    j = 0;
    while(line[i] && line[i] != '\n')
        i++;
    if (line[i] == '\n')
        i++;
    rest = ft_join(NULL, &line[i]);
    ft_free(&line);
    return (rest);
}

int check_nl(char *buffer)
{
    while (*buffer)
    {
        if ((*buffer) == '\n')
            return (1);
        buffer++;
    }
    return(0);
}
void ft_read(int fd, char **line)
{
    char            *buffer;
    int             flag;
    ssize_t          bytes_readed;

    flag = 0;
    buffer = malloc((BUFFER_SIZE + 1));
    if (!buffer)
    {
        ft_free(line);
        return;
    }
    while (!flag)
    {
        bytes_readed = read(fd, buffer, BUFFER_SIZE);
        if (!bytes_readed)
        {
            ft_free(&buffer);
            return ;
        }
        buffer[bytes_readed] = '\0';
        flag = check_nl(buffer);
        *line = ft_join(*line, buffer); 
    }
    ft_free(&buffer);
    return ;
}
char    *get_next_line(int fd)
{
    static char *line;
    char    *new_line;

    if (fd < 0 || read(fd, NULL, 0) == -1 || BUFFER_SIZE <= 0)
    {
        free(line);
        line = NULL;
        return  NULL;
    }
    ft_read(fd, &line);
    if(!line || *line == '\0')
    {
        ft_free(&line);
        return NULL;
    }
    new_line = ft_re_line(line);
    if (!new_line)
    {
        ft_free(&line);
        return NULL;
    }
    line = rest(line);
    if (!line)
        ft_free(&new_line);
    return (new_line);
}
int main()
{
    int fd = open("file.txt", O_CREAT | O_RDWR , 0777);


    printf("%s", get_next_line(fd));
    close(fd);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    // printf("----------------------------\n");

    // printf("%s", get_next_line(fd));
    
    // printf("----------------------------\n");
    
    // printf("%s", get_next_line(fd));

}