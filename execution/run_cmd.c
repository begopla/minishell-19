/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:24 by szubair           #+#    #+#             */
/*   Updated: 2023/04/19 16:56:52 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_last_redir(t_list *hd_contents, t_exec *step,
	int *heredoc_fds, t_redir **inredir)
{
	int			in_fd;

	in_fd = -1;
	*inredir = last_inredir(step->cmd->redirs);
	if (*inredir != NULL)
	{
		if ((*inredir)->type == INPUT_REDIR)
			in_fd = open((*inredir)->file, O_RDONLY);
		else if ((*inredir)->type == HEREDOC)
		{
			pipe(heredoc_fds);
			while (hd_contents != NULL)
			{
				if (hd_contents->content != NULL)
					break ;
				hd_contents = hd_contents->next;
			}
			ft_putstr_fd(hd_contents->content, heredoc_fds[1]);
			ft_free2(&hd_contents->content);
		}
	}
	return (in_fd);
}

int	cmd_init(t_shell *shell, t_redir **inredir, t_exec *step,
	int *heredoc_fds)
{
	int	in_fd;

	*inredir = NULL;
	heredoc_fds[0] = -1;
	heredoc_fds[1] = -1;
	in_fd = -1;
	if (step->cmd->redirs)
		in_fd = open_last_redir(shell->heredoc_contents, step,
				heredoc_fds, inredir);
	return (in_fd);
}

void	pipe_fds(const t_exec *step, int *fds)
{
	if (step->pipe_next)
		pipe(fds);
}

int	*first_cmd(t_exec *step, int *fds, t_shell *shell, int out_fd)
{
	int			in_fd;
	int			heredoc_fds[2];
	int			exit_code;
	t_redir		*inredir;

	in_fd = cmd_init(shell, &inredir, step, heredoc_fds);
	pipe_fds(step, fds);
	if (parent_builtin(step) && !step->pipe_next)
		return (run_parent_builtin(step, shell, fds));
	if (step->cmd->arg_arr[0] != NULL)
		step->cmd->pid = fork();
	if (step->cmd->arg_arr[0] != NULL && step->cmd->pid == 0)
	{
		dup_pipe_fds(inredir, heredoc_fds, step, fds);
		dup_redir_fds(in_fd, out_fd);
		if (is_builtin(step))
		{
			exit_code = run_child_builtin2(shell, step, fds, heredoc_fds);
			
			ft_close(&out_fd);
			ft_close(&in_fd);
			exit(exit_code);
		}
		execve(step->cmd->arg_arr[0], step->cmd->arg_arr, shell->env);
		printf("Is it here I exit (1)\n");
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		ft_close(&g_dupstdin);
		ft_free_array(shell->env);
		ft_free_array(shell->declared_env);
		ft_lstclear(&shell->heredoc_contents, free);
		ft_free2(&shell->fd);
		free_steps(&shell->step);
		free(shell);
	}
	return (close_all(fds, &in_fd, &out_fd, heredoc_fds));
}

int	*other_cmd(t_exec *step, int *fds, t_shell *shell, int out_fd)
{
	int			in_fd;
	int			fdtmp;
	int			heredoc_fds[2];
	int			exit_code;
	t_redir		*inredir;

	fdtmp = fds[0];
	in_fd = cmd_init(shell, &inredir, step, heredoc_fds);
	pipe_fds(step, fds);
	if (step->cmd->arg_arr[0] != NULL)
		step->cmd->pid = fork();
	if (step->cmd->arg_arr[0] != NULL && step->cmd->pid == 0)
	{
		dup_heredoc_fds(inredir, heredoc_fds, &fdtmp);
		dup_pipes_and_redirs(step, fds, in_fd, out_fd);
		if (is_builtin(step))
		{
			exit_code = run_child_builtin(shell, step, fds, heredoc_fds);
			child_builtin_cleanup(&out_fd, &in_fd, &fdtmp, exit_code);
			
		}
		execve(step->cmd->arg_arr[0], step->cmd->arg_arr, shell->env);
		printf("Is it here I exit (2)\n");
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		ft_close(&g_dupstdin);
		ft_free_array(shell->env);
		ft_free_array(shell->declared_env);
		ft_lstclear(&shell->heredoc_contents, free);
		ft_free2(&shell->fd);
		free_steps(&shell->step);
		free(shell);
		//  free(all);
	}
	close_fds(step, fds, &fdtmp);
	return (close_all(fds, &in_fd, &out_fd, heredoc_fds));
}
