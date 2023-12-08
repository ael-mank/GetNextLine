/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:05:27 by ael-mank          #+#    #+#             */
/*   Updated: 2023/12/08 17:39:25 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*ft_fill(int fd, char *stash, char *buffer)
{
	char	*tmp;
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (free(stash), NULL);
		else if (bytesread == 0)
			break ;
		buffer[bytesread] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*ft_collect_leftover(char *line)
{
	char	*leftover;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0)
		return (NULL);
	leftover = ft_substr(line, i + 1, ft_strlen(line) - 1);
	if (*leftover == 0)
	{
		free(leftover);
		leftover = NULL;
	}
	return (leftover);
}

void	ft_update_line(char **line)
{
	char	*tmp;
	char	*out;
	int		len;
	int		i;

	len = 0;
	if (!(*line))
		return ;
	tmp = *line;
	while (tmp[len] && tmp[len] != '\n')
		len++;
	out = ft_calloc(len + 2, sizeof(char));
	if (!out)
		return ;
	i = 0;
	while (i < len)
	{
		out[i] = tmp[i];
		i++;
	}
	out[i] = tmp[i];
	i++;
	out[i] = '\0';
	free(tmp);
	*line = out;
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stash[FD_MAX];

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		free(buffer);
		stash[fd] = NULL;
		buffer = NULL;
		return (0);
	}
	if (!buffer)
		return (NULL);
	line = ft_fill(fd, stash[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash[fd] = ft_collect_leftover(line);
	ft_update_line(&line);
	return (line);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	char	*temp;

	if (size != 0 && count > (size_t)-1 / size)
		return (NULL);
	res = malloc(count * size);
	if (!res)
		return (NULL);
	temp = (char *)res;
	while (count-- > 0)
	{
		*temp = 0;
		temp++;
	}
	return (res);
}

/*
tr -dc "A-Za-z 0-9" < /dev/urandom | fold -w100|head -n 10000 > bigfile.txt
*/
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("bigfile.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	i = 0;
// 	while (line = get_next_line(fd))
// 	{
// 		printf("[%i] : %s\n", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
