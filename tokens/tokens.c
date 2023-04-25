/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:45:15 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/16 02:11:14 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*check_token_errors(char *line, int *error)
{
	size_t	i;
	char	end_char;
	int		is_end;

	i = 0;
	end_char = '\0';
	is_end = 0;
	while (line[i])
	{
		set_quotes_at_end(line[i], &end_char, &is_end);
		if (!is_end && (line[i] == '\\' || line[i] == ';' || line[i] == '`'
				|| (line[i] == '&' && line[i + 1] != '&')
				|| (line[i] == '(' && line[i + 1] == ')')))
		{
			printf("Parse error: Invalid input\n");
			*error = 1;
			return (error);
		}
		if (!is_end && (line[i] == '&' && line[i + 1] != '\0'))
			i++;
		i++;
	}
	return (0);
}

int	first_part_quotes(t_shell *minishell, char *line,
	size_t *i, t_list **tokens)
{
	t_list	*new;

	new = NULL;
	if (line[*i] == '\'')
		new = token_a_single_quote(minishell, line, i);
	else if (line[*i] == '\"')
		new = token_a_double_quote(minishell, line, i,
				!last_was_heredoc(*tokens));
	else if (is_operator(line, *i))
		new = token_operator(line, i);
	else
		new = token_nested_expr(minishell, line, i);
	if (new == NULL)
	{
		ft_lstclear(tokens, free_token);
		return (1);
	}
	ft_lstadd_back(tokens, new);
	return (0);
}

int	second_part_env(t_shell *minishell, char *line, size_t *i, t_list **tokens)
{
	t_list	*new;

	if (line[*i] == '$' && !last_was_heredoc(*tokens))
	{
		new = token_an_env(minishell, line, i);
		if (new == NULL)
		{
			ft_lstclear(tokens, free_token);
			throw_error("Parse error\n");
			return (1);
		}
		if (clean_token_env(&new, tokens))
		{
			ft_lstclear(tokens, free_token);
			return (1);
		}
	}
	else if (line[*i] == ')')
	{
		ft_lstclear(tokens, free_token);
		throw_error("Parse error\n");
		return (1);
	}
	return (0);
}

int	plain_text_part(t_shell *minishell, char *line,
	size_t *idx, t_list **tokens)
{
	t_token	*tkn;
	size_t	i;

	i = *idx;
	tkn = plain_text_part2(idx);
	if (!tkn)
		return (1);
	while (line[i] && ft_strchr(" \'\"|(<&>)", line[i]) == NULL)
		i++;
	if (line[i] == ')')
	{
		throw_error("Parse error\n");
		return (1);
	}
	if (!to_end_of_token(line, &i, tkn))
		return (free_tkn_and_return(tkn, 1));
	while (tkn->expanded && ft_is_dollar_env(tkn->substr))
		tkn->substr = expand_env(minishell, tkn->substr);
	tkn->substr = trim_str_dollar(tkn->substr);
	tkn->substr = trim_str_quotes(tkn->substr);
	if (!tkn->substr)
		return (throw_error_and_return(tkn));
	ft_lstadd_back(tokens, ft_lstnew(tkn));
	*idx = tkn->end;
	return (0);
}

t_list	*tokenize_the_input(t_shell *minishell, char *line, int *error)
{
	t_list	*res;
	size_t	len;

	*error = 0;
	if (check_token_errors(line, error))
		return (NULL);
	res = NULL;
	len = 0;
	while (line[len])
	{
		if (line[len] == '\'' || line[len] == '\"' || is_operator(line, len)
			|| line[len] == '(')
				*error = first_part_quotes(minishell, line, &len, &res);
		else if ((line[len] == '$' && last_was_heredoc(res) == 0)
			|| line[len] == ')')
				*error = second_part_env(minishell, line, &len, &res);
		else if (line[len] != ' ')
			*error = plain_text_part(minishell, line, &len, &res);
		if (*error == 1)
			return (NULL);
		if (line[len] != '\0')
			len++;
	}
	return (res);
}
