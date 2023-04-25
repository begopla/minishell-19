/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:17:52 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/14 12:46:46 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*to_end_of_token(char *line, size_t *y, t_token *tkn)
{
	char	is_quote;

	is_quote = '\0';
	while ((line[*y] == '\'' || line[*y] == '\"') && line[*y])
	{
		is_quote = line[*y];
		*y += 1;
		while (line[*y] && line[*y] != is_quote)
			*y += 1;
		if (line[*y] == '\0')
			return (throw_error("Parse Error: Invalid input\n"));
		*y += 1;
		while (line[*y] && ft_strchr("|&()><", line[*y]) == NULL)
			*y += 1;
		tkn->expanded = 1;
	}
	tkn->end = *y - 1;
	tkn->substr = ft_substr(line, tkn->start, tkn->end - tkn->start + 1);
	return (tkn);
}

static void	avoid_dollar(const char *str, char *new, char *to_check, size_t *i)
{
	*to_check = str[*i + 1];
	*i += 1;
	*new = str[*i];
}

char	*trim_str_dollar(char *str)
{
	size_t	i;
	size_t	y;
	char	*new_str;
	char	to_check;
	int		is_quote;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	y = 0;
	to_check = '\0';
	is_quote = 0;
	while (str[i])
	{
		set_quotes_at_end(str[i], &to_check, &is_quote);
		if (is_quote)
			new_str[y++] = str[i++];
		else if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			avoid_dollar(str, &new_str[y], &to_check, &i);
		else
			new_str[y++] = str[i++];
	}
	ft_free(str);
	return (new_str);
}

int	throw_error_and_return(t_token *tkn)
{
	(void) tkn;
	throw_error(NULL);
	return (1);
}
