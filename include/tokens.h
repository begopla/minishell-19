/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:11:41 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/14 12:44:06 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef enum e_token_type
{
	QUOTED_STRING,
	DOUBLE_QUOTED_STRING,
	NORMAL,
	INPUT_REDIR,
	OUTPUT_REDIR,
	APPEND,
	HEREDOC,
	PIPE,
	SUB_EXPR,
	LAST_EXIT,
	ENV_VAR,
	WILDCARD,
	DUMMY
}t_token_type;

typedef struct s_token
{
	t_token_type	type;
	size_t			start;
	size_t			end;
	char			*substr;
	t_list			*sub_tokens;
	int				expanded;			
}t_token;

void	set_quotes_at_end(char c, char *to_check, int *is_end);
void	return_contrary_boolean(int *check);
int		is_operator(char *line, size_t i);
void	*throw_error(char *msg);
void	ft_is_token_type(t_token_type *type, char *line, size_t *i);
t_list	*ft_lstnew_token(t_token *token);
t_token	*plain_text_part2(size_t *i);
int		throw_error_and_return(t_token *tkn);
int		last_was_heredoc(t_list	*list);
int		clean_token_env(t_list **lst, t_list **tokens);
int		free_tkn_and_return(t_token *tkn, int ret);

#endif
