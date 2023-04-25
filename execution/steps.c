/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:42 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 19:15:44 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*wait_cmds(t_list *steps, t_execflags *flags)
{
	t_exec	*step;

	while (steps && flags->step_num_start < flags->step_num)
	{
		step = steps->content;
		if (step->cmd->arg_arr[0] && !is_dir(step->cmd->arg_arr[0])
			&& (access(step->cmd->arg_arr[0], X_OK) != -1
				|| is_builtin(step)))
		{
			waitpid(step->cmd->pid, &flags->w_status, 0);
		}
		flags->step_num_start++;
		steps = steps->next;
	}
	return (steps);
}

t_list	*reset_to_step(t_list *exec_steps, int step_number_start)
{
	t_list	*steps;
	int		wait_id;

	steps = exec_steps;
	wait_id = 0;
	while (steps && wait_id < step_number_start)
	{
		steps = steps->next;
		wait_id++;
	}
	return (steps);
}
