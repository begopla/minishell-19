/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:33 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:04:25 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_pipe_fds(t_redir *inredir, int *heredoc_fds, t_exec *step,
	int *fd)
{
	if (inredir && inredir->type == HEREDOC)
	{
		ft_close(&heredoc_fds[1]);
		dup2(heredoc_fds[0], 0);
	}
	if (step->pipe_next)
	{
		ft_close(&fd[0]);
		dup2(fd[1], 1);
	}
}

void	dup_redir_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
		dup2(in_fd, 0);
	if (out_fd != -1)
		dup2(out_fd, 1);
}
