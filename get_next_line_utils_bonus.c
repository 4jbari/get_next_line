/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:06:17 by ajbari            #+#    #+#             */
/*   Updated: 2024/02/29 19:44:11 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

char	*ft_join(char *s1, char *s2)
{
	char	*re_line;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) + ft_strlen(s2);
	re_line = malloc((j + 1) * sizeof(char));
	if (!re_line)
	{
		ft_free(&s1);
		return (NULL);
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
