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

#include "get_next_line_bonus.h"

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
	static char	*rest[1024];
	char		*lu;
	char		*line;

	lu = ft_lu(fd, rest[fd]);
	if (lu == NULL)
		return (NULL);
	if (rest[fd])
	{
		line = ft_strjoin(rest[fd], lu);
		free(rest[fd]);
		rest[fd] = NULL;
	}
	else
		line = ft_strdup(lu);
	line = ft_line1(lu, fd, line);
	if (line == NULL)
		return (NULL);
	if (ft_strchr(line, '\n') != 0)
		rest[fd] = ft_rest(line);
	line = ft_line2(line);
	return (line);
}

int     main(void)
{
        int     fd1;
	int     fd2;
	int     fd3;
	int     fd4;
	int     fd5;
        int     cl;
	char	*str;

        fd1 = open("readme1.txt", O_RDONLY);
	fd2 = open("readme2.txt", O_RDONLY);
	fd3 = open("readme3.txt", O_RDONLY);
	fd4 = open("readme4.txt", O_RDONLY);
	fd5 = open("readme5.txt", O_RDONLY);

        printf("open fd1: %d\n", fd1);
	printf("open fd2: %d\n", fd2);
	printf("open fd3: %d\n", fd3);
	printf("open fd4: %d\n", fd4);
	printf("open fd5: %d\n", fd5);

	str = get_next_line(1025);
	printf("line a: %s", str);
	free(str);

	str = get_next_line(fd2);
        printf("line a: %s", str);
        free(str);

	str = get_next_line(fd1);
        printf("line b: %s", str);
	free(str);

	str = get_next_line(fd3);
        printf("line a: %s", str);
        free(str);

	str = get_next_line(fd3);
        printf("line b: %s", str);
        free(str);

	str = get_next_line(fd5);
        printf("line a: %s\n", str);
        free(str);

        cl = close(fd2);
        printf("close fd: %d\n", cl);
}
