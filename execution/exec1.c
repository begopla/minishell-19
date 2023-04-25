/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:49 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:06:27 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_exec	*run_subexpr(t_shell *shell, t_exec *step,
	t_execflags *flags, t_list **steps)
{
	if (exec_subexpr(shell, step, flags, steps) == FALSE)
	{
		flags->action = -1;
		return (step);
	}
	flags->action = 1;
	return (step);
}

bool	exec_subexpr(t_shell *shell, t_exec *step, t_execflags *flags,
	t_list **steps)
{
	int			pid;
	t_list		*sub_steps;
	int			heredocs_to_skip;

	pid = parse_and_fork_subexpr(shell, step, &sub_steps);
	waitpid(pid, &flags->w_status, 0);
	heredocs_to_skip = count_heredocs(sub_steps);
	skip_sub_heredocs(shell->heredoc_contents, heredocs_to_skip);
	step->exit_code = WEXITSTATUS(flags->w_status);
	shell->last_exit_code = step->exit_code;
	if (!(flags->first_flag))
		flags->first_flag = true;
	*steps = (*steps)->next;
	return (true);
}

static bool	run_cmds(t_shell *shell, t_exec *step, t_execflags *flags,
	int out_fd)
{
	if (!flags->first_flag && flags->valid_redirection)
	{
		shell->fd = first_cmd(step, shell->fd, shell, out_fd);
		flags->first_flag = true;
	}
	else if (flags->valid_redirection)
		shell->fd = other_cmd(step, shell->fd, shell, out_fd);
	return (true);
}

t_exec	*run_exec_cmds(t_shell *shell, t_list **steps, int *out_fd,
	t_execflags *flags)
{
	t_exec	*step;

	flags->action = 0;
	step = (*steps)->content;
	if (step->subexpr_line != NULL)
		return (run_subexpr(shell, step, flags, steps));
	flags->exit = FALSE;
	flags->valid_redirection = open_redirs(shell, step, &flags->exit, out_fd);
	set_cmd_path(shell, step);
	check_command(shell, steps, step, flags);
	if (flags->action == -1)
		return (step);
	else if (flags->action == 1)
	{
		ft_close(out_fd);
		return (step);
	}
	if (run_cmds(shell, step, flags, *out_fd) == false)
		flags->action = -1;
	return (step);
}
