/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:45 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:04:59 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_cmds(t_shell *shell, int *out_fd, t_execflags *flags,
	int step_number)
{
	shell->fd[0] = -1;
	shell->fd[1] = -1;
	*out_fd = -1;
	flags->w_status = 0;
	flags->first_flag = false;
	flags->exit = false;
	flags->step_num = step_number;
}

t_list	*begin_step(t_execflags *flags, t_list *exec_steps,
	t_exec **step)
{
	t_list	*steps;

	flags->step_num_start = 0;
	steps = exec_steps;
	while (flags->step_num_start < flags->step_num && steps != NULL)
	{
		steps = steps->next;
		flags->step_num_start++;
	}
	if (steps == NULL)
		return (NULL);
	*step = steps->content;
	return (steps);
}

t_list	*wait_and_get_exit(t_shell *shell, t_exec *step,
	t_list *exec_steps, t_execflags *flags)
{
	t_list	*steps;
	int		i;

	if (step->cmd)
	{
		steps = reset_to_step(exec_steps, flags->step_num_start);
		steps = wait_cmds(steps, flags);
		shell->last_exit_code = get_exit(exec_steps, step, flags);
	}
	else
	{
		i = 1;
		steps = exec_steps;
		while (steps && i < flags->step_num)
		{
			steps = steps->next;
			i++;
		}
	}
	return (steps);
}

void	exec_cmds(t_shell *shell, t_list *exec_steps, int step_number,
	char *current_line)
{
	t_exec			*step;
	t_list			*steps;
	t_execflags		flags;
	int				out_fd;

	init_cmds(shell, &out_fd, &flags, step_number);
	steps = begin_step(&flags, exec_steps, &step);
	if (steps == NULL)
		return ;
	while (steps)
	{
		flags.step_num++;
		step = run_exec_cmds(shell, &steps, &out_fd, &flags);
		if (flags.action == 1)
			continue ;
		if (flags.action == -1)
			break ;
		steps = steps->next;
	}
	ft_close(&shell->fd[0]);
	ft_close(&out_fd);
	steps = wait_and_get_exit(shell, step, exec_steps, &flags);
	shell->current_line = current_line;
}
