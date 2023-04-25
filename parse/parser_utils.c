/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:04:12 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/24 14:45:30 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_pipe(t_token *token)
{
	if (token->type == PIPE)
		return (1);
	return (0);
}

int	redirection(t_token *token)
{
	if (token->type == INPUT_REDIR || token->type == OUTPUT_REDIR
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

int	errors_in_tkn(t_list *copy)
{
	t_token	*token;
	t_list	*tokens;
	t_token	*n_tok;

	tokens = copy;
	if (!tokens)
		return (0);
	token = (t_token *)tokens->content;
	if ((ft_lstsize(tokens) == 1 && redirection(token))
		|| (is_pipe(ft_lstlast(tokens)->content) || is_pipe(token)))
		return (1);
	while (tokens->next)
	{
		token = (t_token *)tokens->content;
		n_tok = (t_token *)tokens->next->content;
		if ((is_pipe(token) && is_pipe(n_tok))
			|| (redirection(token) && redirection(n_tok))
			|| (redirection(token) && is_pipe(n_tok))
		//  Do we need this combinations too? /// 
			|| (redirection(token) && n_tok->expanded
			&& (token->type == OUTPUT_REDIR || token->type == APPEND))
			|| (redirection(token) && n_tok->type == SUB_EXPR)
			|| (token->type == SUB_EXPR && redirection(n_tok))
			|| (token->type == PIPE && n_tok->type == SUB_EXPR))
				return (1);
		tokens = tokens->next;
	}
	return (0);
}

// void	convert_str_to_arr(void *step_ptr)
// {
// 	t_list		*arg_list;
// 	size_t		i;
// 	size_t		list_size;
// 	t_exec		*step;

// 	step = step_ptr;
// 	if (step->cmd == NULL)
// 		return ;
// 	arg_list = step->cmd->args;
// 	list_size = ft_lstsize(arg_list);
// 	step->cmd->arg_arr = ft_calloc(list_size + 1, sizeof(char *));
// 	if (step->cmd->arg_arr == NULL)
// 		exit(1);
// 	i = 0;
// 	while (arg_list != NULL)
// 	{
// 		if (arg_list->content == NULL)
// 			step->cmd->arg_arr[i] = NULL;
// 		else
// 			step->cmd->arg_arr[i] = ft_strdup(arg_list->content);
// 		arg_list = arg_list->next;
// 		i++;
// 	}
// 	ft_lstclear(&step->cmd->args, free);
// 	step->cmd->arg_arr[i] = NULL;
// }

void	convert_str_to_arr(void *step_ptr)
{
    t_list  *arg_list;
    t_list  *tmp;
    size_t  i;
    size_t  list_size;
    t_exec  *step;

    tmp = NULL;
    step = step_ptr;
    if (step->cmd == NULL)
        return ;
    arg_list = step->cmd->args;
    list_size = ft_lstsize(arg_list);
    step->cmd->arg_arr = ft_calloc(list_size + 1, sizeof(char *));
    if (step->cmd->arg_arr == NULL)
        exit(1);
    i = 0;
    while (arg_list != NULL)
    {
        if (arg_list->content == NULL)
            step->cmd->arg_arr[i] = NULL;
        else
            step->cmd->arg_arr[i] = ft_strdup(arg_list->content);
        tmp = arg_list;
        ft_free(tmp->content); // free content of tmp before freeing tmp itself
        arg_list = arg_list->next;
        ft_free(tmp);
        i++;
    }
    ft_lstclear(&step->cmd->args, NULL); // pass NULL as the second argument to ft_lstclear since we've already freed the content of each node
   step->cmd->args = NULL; // set arg_list to NULL after freeing all its nodes
    step->cmd->arg_arr[i] = NULL;
}
