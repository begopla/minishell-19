/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:52:58 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/11 14:26:39 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*trim_quotes(char *str, int count)
{
	size_t	i;
	size_t	z;
	char	val;
	char	*res;

	i = 0;
	z = 0;
	res = ft_calloc(ft_strlen(str) - count + 1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			val = str[i];
			i++;
			while (str[i] != val)
				res[z++] = str[i++];
			i++;
		}
		else
			res[z++] = str[i++];
	}
	ft_free(str);
	return (res);
}

char	*trim_str_quotes(char *str)
{
	char	val;
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			val = str[i++];
			count += 2;
			while (str[i] && str[i] != val)
				i++;
			if (!str[i])
			{
				ft_free(str);
				return (NULL);
			}
			i++;
		}
		else
			i++;
	}
	return (trim_quotes(str, count));
}
