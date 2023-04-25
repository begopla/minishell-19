/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:10:38 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/14 12:46:04 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_was_heredoc(t_list	*list)
{
	t_token	*token;

	if (list)
	{
		token = (t_token *) ft_lstlast(list)->content;
		if (token->type == HEREDOC)
			return (1);
	}
	return (0);
}

void	set_quotes(const char ch, char *quote, int *in_quote)
{
	if (ch == '\'' || ch == '\"')
	{
		if (*quote == '\0')
		{
			*quote = ch;
			*in_quote = !(*in_quote);
		}
		else if (*quote == ch)
		{
			*in_quote = !(*in_quote);
			*quote = '\0';
		}
	}
}

t_list	*tokenize_inside_envvar(const char *line,
	size_t *idx)
{
	size_t	i;
	t_token	*tkn;
	t_list	*el;

	i = *idx;
	tkn = ft_calloc(1, sizeof(t_token));
	if (tkn == NULL)
		return (NULL);
	tkn->start = i;
	tkn->type = NORMAL;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	tkn->end = i - 1;
	tkn->substr = ft_substr(line, tkn->start, tkn->end - tkn->start + 1);
	el = ft_lstnew(tkn);
	*idx = tkn->end;
	return (el);
}

t_token	*plain_text_part2(size_t *i)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->start = *i;
	tkn->type = NORMAL;
	return (tkn);
}

int	free_tkn_and_return(t_token *tkn, int ret)
{
	free_token(tkn);
	return (ret);
}
