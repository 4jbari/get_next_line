/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:48:58 by ajbari            #+#    #+#             */
/*   Updated: 2024/03/01 16:25:35 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_re_line(char *line)
{
	char	*return_line;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return_line = malloc((i + 1) * sizeof(char));
	if (!return_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
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
	return (return_line);
}

char	*rest(char *line)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	rest = ft_join(NULL, &line[i]);
	ft_free(&line);
	return (rest);
}

int	check_nl(char *buffer)
{
	while (*buffer)
	{
		if ((*buffer) == '\n')
			return (1);
		buffer++;
	}
	return (0);
}

void	ft_read(int fd, char **line)
{
	char	*buffer;
	int		flag;
	ssize_t	bytes_readed;

	flag = 0;
	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
	{
		ft_free(line);
		return ;
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

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*new_line;

	new_line = NULL;
	if (fd < 0)
		return (NULL);
	if (read(fd, new_line, 0) == -1 || BUFFER_SIZE <= 0)
		return (ft_free(&line[fd]));
	ft_read(fd, &line[fd]);
	if (!line[fd] || *line[fd] == '\0')
		return (ft_free(&line[fd]));
	new_line = ft_re_line(line[fd]);
	if (!new_line)
		return (ft_free(&line[fd]));
	line[fd] = rest(line[fd]);
	return (new_line);
}
