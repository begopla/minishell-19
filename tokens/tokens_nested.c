/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_nested.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:54:43 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/11 14:19:48 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return_nbr_subexpr(char *line, size_t *y)
{
	int		n_expr;

	n_expr = 1;
	while (line[*y])
	{
		if (line[*y] == '(')
			n_expr++;
		else if (line[*y] == ')')
			n_expr--;
		if (n_expr < 0)
			break ;
		*y = *y + 1;
	}
	return (n_expr);
}

t_list	*token_nested_expr(t_shell *minishell, char *line, size_t *i)
{
	t_token	*tok;
	size_t	y;
	int		error;

	tok = ft_calloc(1, sizeof(t_token));
	tok->start = *i;
	y = *i + 1;
	tok->type = SUB_EXPR;
	if (!tok)
		return (NULL);
	if (ft_return_nbr_subexpr(line, &y) < 0)
		return (throw_error("Parse Error: Invalid parenthesis input\n"));
	tok->end = y - 1;
	tok->substr = ft_substr(line, tok->start + 1, tok->end - tok->start -1);
	if (!tok->substr)
	{
		free(tok);
		return (NULL);
	}
	error = 0;
	tok->sub_tokens = tokenize_the_input(minishell, tok->substr, &error);
	if (error)
		return (NULL);
	*i = tok->end;
	return (ft_lstnew(tok));
}
