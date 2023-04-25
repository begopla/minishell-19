/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:06 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:07:26 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_heredocs(t_list *substeps)
{
	int			num_heredocs;
	t_exec		*step;
	t_redir		*last_redir;

	num_heredocs = 0;
	while (substeps != NULL)
	{
		step = substeps->content;
		if (step->cmd != NULL && step->cmd->redirs != NULL)
		{
			last_redir = last_inredir(step->cmd->redirs);
			if (last_redir != NULL)
				num_heredocs++;
		}
		substeps = substeps->next;
	}
	return (num_heredocs);
}

void	skip_sub_heredocs(t_list *heredocs, int num_skipped)
{
	int	i;

	i = 0;
	if (num_skipped == 0)
		return ;
	while (heredocs != NULL && heredocs->content == NULL)
		heredocs = heredocs->next;
	if (heredocs == NULL)
		return ;
	while (i < num_skipped)
	{
		ft_free2(&heredocs->content);
		heredocs->content = NULL;
		heredocs = heredocs->next;
		i++;
	}
}
