/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:50:39 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 16:12:39 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

static size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (i < srcsize && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

static char	*ft_strdup_gnl(const char *src)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(src) + 1;
	dst = malloc(len);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy_gnl(dst, src, len);
	return (dst);
}

static char	*ft_strjoin_gnl(char *s1, char const *s2, size_t len)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = len;
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy_gnl(join, s1, s1_len + 1);
	ft_strlcpy_gnl((join + s1_len), s2, s2_len + 1);
	free(s1);
	return (join);
}

static void	set_new_buf(char *buf, char *line, char *newline)
{
	int	to_copy;

	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strlcpy_gnl(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		ft_strlcpy_gnl(buf, "", BUFFER_SIZE + 1);
	}
	line[to_copy] = '\0';
}

/**
 * The function `get_next_line` reads a line from a file descriptor and
 * returns it as a string.
 * 
 * @param fd The parameter "fd" is an integer representing the file descriptor
 * of the file you want to read from.
 * 
 * @return a pointer to a character, which represents the next line read from
 * the file descriptor specified by `fd`.
 */
char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			countread;

	line = ft_strdup_gnl(buf);
	while (!ft_strchr(line, '\n'))
	{
		countread = read(fd, buf, BUFFER_SIZE);
		if (countread > 0)
		{
			buf[countread] = '\0';
			line = ft_strjoin_gnl(line, buf, countread);
		}
		else
			break ;
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	set_new_buf(buf, line, newline);
	return (line);
}
