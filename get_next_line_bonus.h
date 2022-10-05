/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoffo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:18:25 by ljoffo            #+#    #+#             */
/*   Updated: 2021/12/31 15:18:31 by ljoffo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h> // for open
# include <sys/stat.h>	// for open
# include <fcntl.h>	// for open
# include <stdio.h>	// for printf
# include <unistd.h>	// for close and read
# include <stdlib.h>	// for malloc and free

char	*ft_strdup(const char *s);
char	*ft_strdup2(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
