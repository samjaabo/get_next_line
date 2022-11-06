/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:16:42 by samjaabo          #+#    #+#             */
/*   Updated: 2022/11/06 12:57:18 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *s1, char *s2)
{
	char	*res;
	char	*ss1;
	char	*ss2;
	char	*cpy;

	ss1 = s1;
	ss2 = s2;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free(s1), free(s2), NULL);
	cpy = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	free(ss1);
	free(ss2);
	return (cpy);
}

char	*ft_read(int fd, int *count, int *eof)
{
	char	*str;
	char	*cpy;
	int		n;

	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	n = read(fd, str, BUFFER_SIZE);
	if (n <= -1)
		return (free(str), NULL);
	str[n] = '\0';
	if (n != BUFFER_SIZE)
		*eof = 1;
	n = 0;
	cpy = str;
	while (*cpy)
		if (*cpy++ == '\n')
			++n;
	*count += n;
	return (str);
}

char	*get_line(char *data, int *count, int *lock)
{
	char	*cpy;
	char	*str;
	int		len;

	if (*lock == 1)
		return (NULL);
	if (*count == 0 && *lock == 0)
	{
		*lock = 1;
		return (data);
	}
	len = 0;
	while (data[len] && data[len] != '\n')
		++len;
	++len;
	str = malloc(len + 1);
	if (!str)
		return (free(data), NULL);
	cpy = str;
	while (len--)
		*cpy++ = *data++;
	*cpy = '\0';
	*count -= 1;
	return (str);
}

char	*del_line(char *data)
{
	char	*str;
	char	*save;
	char	*cpy;

	if (!data || *data == '\0')
		return (NULL);
	str = data;
	while (*str && *str != '\n')
		++str;
	if (!*str)
		return (data);
	++str;
	save = malloc(ft_strlen(str) + 1);
	if (!save)
		return (free(data), NULL);
	cpy = save;
	while (*str)
		*cpy++ = *str++;
	*cpy = '\0';
	free(data);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*data;
	static int	count;
	static int	eof;
	static int	lock;
	char		*rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!eof && count <= 0)
	{
		rd = ft_read(fd, &count, &eof);
		if (!rd)
			return (free(data), NULL);
		data = ft_join(data, rd);
		if (!data)
			return (NULL);
	}
	if (count == 0 && !eof)
		return (get_next_line(fd));
	rd = get_line(data, &count, &lock);
	data = del_line(data);
	if (!data)
		return (free(rd), NULL);
	return (rd);
}
