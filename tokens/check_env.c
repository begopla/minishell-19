/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:31:04 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/06 14:40:16 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_contrary_boolean(int *check)
{
	if (*check)
		*check = 0;
	else
		*check = 1;
}

void	set_quotes_at_end(char c, char *to_check, int *is_end)
{
	if (c == '\'' || c == '\"')
	{
		if (*to_check == '\0')
		{
			*to_check = c;
			return_contrary_boolean(is_end);
		}
		else if (*to_check == c)
		{
			*to_check = '\0';
			return_contrary_boolean(is_end);
		}
	}
}

void	return_set_double(const char *str, const size_t i, int *single,
	int *isdouble)
{
	if (str[i] == '\'' && !*isdouble)
		return_contrary_boolean(single);
	if (str[i] == '\"' && !*single)
		return_contrary_boolean(isdouble);
}

static int	correct_doll_var(const char *str, size_t *i)
{
	if (str[*i] == '\0')
		return (0);
	else if (str[*i] == '?')
		return (1);
	else if ((str[*i] == '\"' || str[*i] == '\''))
	{
		if (str[*i + 1] == '\0')
			return (0);
		else if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_')
			*i += 1;
		else
			return (1);
	}
	else if (!ft_isalnum(str[*i]) && str[*i] != '_')
		*i += 1;
	else
		return (1);
	if (str[*i] == '\0')
		return (0);
	return (-1);
}

int	ft_is_dollar_env(char *str)
{
	size_t	i;
	int		single;
	int		isdouble;
	int		is_env;

	i = 0;
	single = 0;
	isdouble = 0;
	while (str[i] != '\0')
	{
		return_set_double(str, i, &single, &isdouble);
		if (str[i] == '$' && !single)
		{
			i++;
			is_env = correct_doll_var(str, &i);
			if (!is_env)
				return (0);
			if (is_env)
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}
