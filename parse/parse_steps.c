/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:13:34 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/24 16:50:42 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_next_subexp(t_list *tokens, t_token **t_content, int *error)
{
	if (tokens->next)
	{
		*t_content = tokens->next->content;
		if ((*t_content)->type == PIPE)
		{
			*error = 1;
			return (0);
		}
		if ((*t_content)->type == SUB_EXPR
			|| (*t_content)->type == QUOTED_STRING
			|| (*t_content)->type == NORMAL
			|| (*t_content)->type == DOUBLE_QUOTED_STRING)
		{
			*error = 1;
			return (0);
		}
	}
	return (1);
}

int	parse_subexpr(t_token *t_content, t_list **steps, t_list *tokens,
	int *error)
{
	t_exec	*ex_step;

	ex_step = ft_calloc(1, sizeof(t_exec));
	if (!ex_step)
	{
		*error = 1;
		return (0);
	}
	ex_step->subexpr_line = ft_strdup(t_content->substr);
	ft_lstadd_back(steps, ft_lstnew(ex_step));
	if (check_next_subexp(tokens, &t_content, error))
		return (0);
	return (1);
}

// void	free_cmd(void *cmd_void)
// {
// 	t_cmd	*cmd;

// 	cmd = (t_cmd *)cmd_void;
// 	if (!cmd)
// 		return ;
// 	ft_lstclear(&cmd->args, free);
// 	ft_lstclear(&cmd->redirs, free_redir);
// 	if (cmd->arg_arr)
// 	{
// 		free(cmd->arg_arr);
// 		cmd->arg_arr = NULL;
// 	}
// 	free(cmd);
// }

// void	free_exec(void *exec_void)
// {
// 	t_exec	*exec;

// 	exec = (t_exec *)exec_void;
// 	if (!exec)
// 		return ;
// 	free_cmd(exec->cmd);
// 	if (exec->subexpr_line)
// 		free(exec->subexpr_line);
// 	free(exec);
// }

// static void del_exec(void *content)
// {
//     free_exec((t_exec *)content);
// }


static t_list	*parse_commands(t_list **tokens, t_token **t_content,
	t_list **steps, int *error)
{
	t_list	*start;
	t_exec	*ex_step;

	(void) t_content;
	(void) error;
	ex_step = NULL;
	start = *tokens;
	while ((*tokens)->next && !is_pipe((*tokens)->next->content))
	{
		*t_content = (*tokens)->content;
		if ((*t_content)->type == SUB_EXPR)
		{
			*error = 1;
			return (*steps);
		}
		(*tokens) = (*tokens)->next;
	}
	ex_step = create_exec(start, *tokens, t_content, *tokens);
	if (!ex_step)
	{
		*error = 1;
		return (NULL);
	}
	ft_lstadd_back(steps, ft_lstnew(ex_step));
	ft_lstdelone(ft_lstlast(*steps), NULL); // Free the last node in the list
	//ft_lstdelone(ft_lstlast(*steps), del_exec);
	return (*steps);
}

t_list	*ft_get_steps(t_list *tokens, int *error)
{
	t_token	*tk_ctnt;
	t_list	*steps;

	steps = NULL;
	tk_ctnt = NULL;
	*error = 0;
	*error = errors_in_tkn(tokens);
	if (*error)
		return (NULL);
	while (tokens)
	{
		tk_ctnt = (t_token *) tokens->content;
		tk_ctnt = tokens->content;
		if (tk_ctnt->type == SUB_EXPR)
			parse_subexpr(tk_ctnt, &steps, tokens, error);
		else if (!is_pipe(tk_ctnt))
			steps = parse_commands(&tokens, &tk_ctnt, &steps, error);
		if (*error)
			return (steps);
		tokens = tokens->next;
	}
	ft_lstiter(steps, convert_str_to_arr);
	*error = 0;
	return (steps);
}
