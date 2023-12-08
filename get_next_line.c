/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:05:27 by ael-mank          #+#    #+#             */
/*   Updated: 2023/12/08 12:13:24 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char *ft_fill(int fd, char *stash, char *buffer)
{
	char *tmp;
	ssize_t bytesread;
	
	bytesread =  1;
	while(bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (free(stash), NULL);
		else if (bytesread == 0)
			break;
		buffer[bytesread] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return(stash);
}

static char *ft_collect_line(char *line)
{
	char *leftover;
	ssize_t i;

	i = 0;
	while(line[i] != '\n' && line[i] != '\0')
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

char	*get_next_line(int fd)
{
	char *line;
	char *buffer;
	static char *stash;
	
	
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (0);
	}
	if (!buffer)
		return(NULL);
	line = ft_fill(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = ft_collect_line(line);
	return(line);
}

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    int i = 0;
    while (i < 25)
    {
        line = get_next_line(fd);
        printf("[%i] : %s\n", i, line);
        i++;
        free(line);
    }
    close(fd);
}
