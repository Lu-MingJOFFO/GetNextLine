/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoffo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:23:16 by ljoffo            #+#    #+#             */
/*   Updated: 2022/01/10 12:37:26 by ljoffo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_lu(int fd, char *rest)
{
	char	*lu;
	int		ret;

	lu = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!lu)
		return (NULL);
	if (rest && ft_strchr(rest, '\n') != 0)
		ret = 0;
	else
	{
		ret = read(fd, lu, BUFFER_SIZE);
		if (ret == -1)
		{
			free(lu);
			return (NULL);
		}
	}
	lu[ret] = '\0';
	return (lu);
}

static char	*ft_line1(char *lu, int fd, char *line)
{
	char	*temp;
	int		ret;

	if (line[0] == '\0')
	{
		free(lu);
		free(line);
		return (NULL);
	}
	while (ft_strchr(line, '\n') == 0 && lu[0] != '\0')
	{
		ret = read(fd, lu, BUFFER_SIZE);
		if (ret == -1)
		{
			free(lu);
			free(line);
			return (NULL);
		}
		lu[ret] = '\0';
		temp = ft_strjoin(line, lu);
		free(line);
		line = temp;
	}
	free(lu);
	return (line);
}

static char	*ft_line2(char *line1)
{
	char	*line2;

	if (ft_strchr(line1, '\n') == 0)
		line2 = ft_strdup(line1);
	else
		line2 = ft_strdup2(line1);
	free(line1);
	return (line2);
}

static char	*ft_rest(char *line1)
{
	char	*rest;
	int		i;

	i = 0;
	while (line1[i] && line1[i] != '\n')
		i++;
	rest = ft_strdup(line1 + i + 1);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*lu;
	char		*line;

	lu = ft_lu(fd, rest);
	if (lu == NULL)
		return (NULL);
	if (rest)
	{
		line = ft_strjoin(rest, lu);
		free(rest);
		rest = NULL;
	}
	else
		line = ft_strdup(lu);
	line = ft_line1(lu, fd, line);
	if (line == NULL)
		return (NULL);
	if (ft_strchr(line, '\n') != 0)
		rest = ft_rest(line);
	line = ft_line2(line);
	return (line);
}
/*
int     main(void)
{
        int     fd;
        int     cl;
	char	*str;

        fd = open("readme.txt", O_RDONLY);

        printf("open fd: %d\n", fd);

	str = get_next_line(fd);
	printf("line1: %s", str);
	free(str);

	str = get_next_line(fd);
        printf("line2: %s", str);
        free(str);

	str = get_next_line(fd);
        printf("line3: %s", str);
        free(str);

	str = get_next_line(fd);
        printf("line4: %s", str);
        free(str);

	str = get_next_line(fd);
        printf("line5: %s", str);
        free(str);

	str = get_next_line(fd);
        printf("line6: %s\n", str);
        free(str);

        cl = close(fd);
        printf("close fd: %d\n", cl);
}*/
