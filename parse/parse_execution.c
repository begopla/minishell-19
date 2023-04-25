/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:46:23 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/19 16:53:50 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_redir	*add_the_redir(t_token **token, t_list **start, t_exec *step)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = (*token)->type;
	*start = (*start)->next;
	if (*start == NULL || redir == NULL)
	{
		ft_free(redir);
		ft_lstclear(&step->cmd->args, free);
		ft_lstclear(&step->cmd->redirs, free_redir);
		return (NULL);
	}
	*token = (*start)->content;
	if (redirection(*token))
	{
		ft_free(redir);
		ft_lstclear(&step->cmd->args, free);
		ft_lstclear(&step->cmd->redirs, free_redir);
		return (NULL);
	}
	if (redir->type != HEREDOC)
		redir->file = ft_strdup((*token)->substr);
	else
		redir->limiter = ft_strdup((*token)->substr);
	return (redir);
}

int	parsing_error(t_redir *redir, t_exec *step)
{
	(void) redir;
	ft_lstclear(&step->cmd->args, free);
	ft_lstclear(&step->cmd->redirs, free_redir);
	ft_free(redir); // This making this command leak:
		//sort < file.txt > (sorted_file.txt)
	return (0);
}

static int	fill_ex_step(t_exec *estp, t_list *start, t_list *end)
{
	t_redir	*r_file;
	t_token	*tkn;

	r_file = NULL;
	while (start && start != end->next)
	{
		tkn = start->content;
		if (redirection(tkn))
		{
			r_file = add_the_redir(&tkn, &start, estp);
			if (!r_file)
				return (0);
			ft_lstadd_back(&estp->cmd->redirs, ft_lstnew(r_file));
		}
		else if (tkn->type == DOUBLE_QUOTED_STRING
			||tkn->type == QUOTED_STRING || tkn->type == NORMAL)
			ft_lstadd_back(&estp->cmd->args, ft_lstnew(ft_strdup(tkn->substr)));
		else if (tkn->type == SUB_EXPR)
			return (parsing_error(r_file, estp));
		start = start->next;
	}
	return (1);
}

static int	check_next_token(t_list *end, t_token **token,
	t_exec *step, t_list *tokens)
{
	if (end->next)
	{
		*token = end->next->content;
		if ((*token)->type == PIPE)
			step->pipe_next = 1;
		*token = tokens->next->next->content;
		if ((*token)->type == PIPE)
			return (0);
	}
	return (1);
}

t_exec	*create_exec(t_list *start, t_list *end, t_token **t_content,
	t_list *tokens)
{
	t_exec	*ex_step;

	ex_step = ft_calloc(1, sizeof(t_exec));
	if (!ex_step)
		return (NULL);
	ex_step->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!ex_step->cmd)
		return (NULL);
	if (!fill_ex_step(ex_step, start, end))
	{
		ft_free(ex_step->cmd);
		ft_free(ex_step);
		return (NULL);
	}
	if (!check_next_token(end, t_content, ex_step, tokens))
		return (NULL);
	return (ex_step);
}
