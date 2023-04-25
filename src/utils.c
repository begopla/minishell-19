/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:45:41 by szubair           #+#    #+#             */
/*   Updated: 2023/04/14 22:43:55 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*join_and_free(char *s1, char *s2, int type)
{
	char	*str;

	if (s1 && s2)
	{
		str = ft_strjoin(s1, s2);
		if (type == 1)
			ft_free(s1);
		else if (type == 2)
			ft_free(s2);
		else if (type == 3)
		{
			ft_free(s1);
			ft_free(s2);
		}
		return (str);
	}
	return (NULL);
}

char	*strjoin_and_free(char *s1, char *s2, int type)
{
	char	*str;

	if (s1 && s2)
	{
		str = ft_strjoin(s1, s2);
		if (type == 1)
			ft_free(s1);
		else if (type == 2)
			ft_free(s2);
		else if (type == 3)
		{
			ft_free(s1);
			ft_free(s2);
		}
		return (str);
	}
	return (NULL);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\f'
		|| c == '\n' || c == '\r'
		|| c == '\t' || c == '\v');
}

static long	ft_atox_helper(const char *str, int i, int *check)
{
	long	temp;
	long	num;

	num = 0;
	temp = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = num;
		num *= 10;
		num += str[i++] - '0';
		if (temp > num)
		{
			*check = 0;
			return (-1);
		}
	}
	return (num);
}

long	ft_atox(const char *str, int *check)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	*check = 1;
	while (is_whitespace(str[i]))
		i++;
	if (ft_strncmp(&str[i], "-9223372036854775808", 20) == 0)
		return (LONG_MIN);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_atox_helper(str, i, check) * sign);
}

void	ft_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}
