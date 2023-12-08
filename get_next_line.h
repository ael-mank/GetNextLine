/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:03:54 by ael-mank          #+#    #+#             */
/*   Updated: 2023/12/08 11:22:51 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char *get_next_line(int fd);

//Utils

char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
char		*ft_strchr(char *str, int c);
char		*ft_strdup(const char *source);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif