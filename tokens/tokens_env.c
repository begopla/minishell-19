/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:19:50 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/19 13:49:28 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*tokenize_env_var_str(char *line)
{
	size_t	i;
	t_list	*tokens;

	tokens = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			ft_lstadd_back(&tokens, tokenize_inside_envvar(line, &i));
		if (line[i] != '\0')
			i++;
	}
	return (tokens);
}

int	retokenize_env_var(t_token *token, t_list **el, t_list **tokens)
{
	char	*substr_copy;

	substr_copy = ft_strdup(token->substr);
	ft_lstclear(el, free_token);
	*el = tokenize_env_var_str(substr_copy);
	if(substr_copy)
		ft_free(substr_copy);
	ft_lstadd_back(tokens, *el);
	return (1);
}

int	clean_token_env(t_list **lst, t_list **tokens)
{
	t_token	*token;

	token = (*lst)->content;
	if (token->substr == NULL)
		ft_lstclear(lst, free_token);
	else if (ft_strncmp(token->substr, "$\"\"", 3) == 0)
	{
		ft_free(&token->substr);
		token->substr = ft_strdup("");
		ft_lstadd_back(tokens, *lst);
	}
	else if (ft_strlen(token->substr) != 0
		&& ft_strchr(token->substr, '$') != NULL)
		ft_lstadd_back(tokens, *lst);
	else if (ft_strlen(token->substr) != 0)
	{
		if (retokenize_env_var(token, lst, tokens))
			return (0);
	}
	else
	{
		token->type = DUMMY;
		ft_lstadd_back(tokens, *lst);
	}
	return (1);
}

static char	*get_env_string(const char *line, size_t *idx)
{
	char	*str;
	size_t	i;
	int		in_quote;
	char	quote;

	i = *idx;
	in_quote = 0;
	quote = '\0';
	while (line[i] != '\0')
	{
		set_quotes(line[i], &quote, &in_quote);
		if ((line[i] == ' ' || ft_strchr("<>|(&)", line[i])) && !in_quote)
			break ;
		i++;
	}
	if (in_quote == 1)
	{
		*idx = i;
		return (NULL);
	}
	str = ft_substr(line, *idx, i - *idx);
	*idx = i - 1;
	return (str);
}

t_list	*token_an_env(t_shell *shell, char *line, size_t *idx)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->type = ENV_VAR;
	tkn->substr = get_env_string(line, idx);
	if (tkn->substr == NULL)
	{
		ft_free(&tkn);
		return (NULL);
	}
	if (ft_strncmp(tkn->substr, "$\"\"", ft_strlen(tkn->substr)) == 0
		&& ft_strlen(tkn->substr) == 3)
	{
		tkn->type = NORMAL;
		return (ft_lstnew(tkn));
	}
	if (ft_is_dollar_env(tkn->substr))
	{
		tkn->substr = expand_env(shell, tkn->substr);
		tkn->type = NORMAL;
	}
	return (ft_lstnew(tkn));
}
