/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:05:46 by samiyazubai       #+#    #+#             */
/*   Updated: 2023/04/16 02:47:54 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//char	*read_buffer(int fd, char *all)
//{
//	char	*str;
//	int		n_readbytes;

//	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
//	if (!str)
//		return (NULL);
//	n_readbytes = 1;
//	while (ft_strchr(all, '\n') == 0 && n_readbytes != 0)
//	{
//		n_readbytes = read(fd, str, BUFFER_SIZE);
//		if (n_readbytes == -1)
//		{
//			free(str);
//			return (NULL);
//		}
//		str[n_readbytes] = '\0';
//		all = ft_strjoin(all, str);
//	}
//	free(str);
//	return (all);
//}

//char	*ft_get_line(char *all)
//{
//	int		i;
//	char	*line;

//	i = 0;
//	if (!all[i])
//		return (NULL);
//	while (all[i] && all[i] != '\n')
//		i++;
//	line = (char *)malloc(sizeof(char) * (i + 2));
//	if (!line)
//		return (NULL);
//	i = 0;
//	while (all[i] && all[i] != '\n')
//	{
//		line[i] = all[i];
//		i++;
//	}
//	if (all[i] == '\n')
//	{
//		line[i] = all[i];
//		i++;
//	}
//	line[i] = '\0';
//	return (line);
//}

//char	*remain(char *all)
//{
//	int		i;
//	int		j;
//	char	*str;

//	i = 0;
//	while (all[i] && all[i] != '\n')
//		i++;
//	if (!all[i])
//	{
//		free(all);
//		return (NULL);
//	}
//	str = (char *)malloc(sizeof(char) * (ft_strlen(all) - i + 1));
//	if (!str)
//		return (NULL);
//	i++;
//	j = 0;
//	while (all[i])
//		str[j++] = all[i++];
//	str[j] = '\0';
//	free(all);
//	return (str);
//}

//char	*get_next_line(int fd)
//{
//	char		*line;
//	static char	*left_str;

//	if (fd < 0 || BUFFER_SIZE <= 0)
//		return (0);
//	left_str = read_buffer(fd, left_str);
//	if (!left_str)
//		return (NULL);
//	line = ft_get_line(left_str);
//	left_str = remain(left_str);
//	return (line);
//}

char	*ft_gnl_free(char *str, char *s)
{
	free(s);
	free(str);
	return (NULL);
}

char	*ft_readline(int fd, char *s, size_t buff)
{
	char	*str;
	int		i;

	i = 1;
	str = (char *)malloc(buff + 1);
	if (!str)
		return (NULL);
	while (i != 0 && !ft_strchr(s, '\n'))
	{
		i = read(fd, str, buff);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		s = ft_gnl_strjoin(s, str);
	}
	if (s[0] == '\0')
	{
		ft_gnl_free(str, s);
		return (NULL);
	}
	free (str);
	return (s);
}

char	*ft_currentline(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_newline(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(ft_strlen(str) - i + 1);
	if (!s)
		return (NULL);
	i++;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free (str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		if (str != NULL)
			free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_readline(fd, str, BUFFER_SIZE);
	if (!str)
		return (NULL);
	s = ft_currentline(str);
	str = ft_newline(str);
	return (s);
}
