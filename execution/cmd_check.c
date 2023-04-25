/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:28 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:03:49 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_invalid_path(t_exec *step)
{
	return (step->cmd->arg_arr[0] && access(step->cmd->arg_arr[0], X_OK) != -1
		&& !ft_strchr(step->cmd->arg_arr[0], '/'));
}

int	check_invalid_command(t_exec *step, int valid_redirs)
{
	return (step->cmd->arg_arr[0] && ((access(step->cmd->arg_arr[0], X_OK) == -1
				&& !is_builtin(step)) || is_dir(step->cmd->arg_arr[0])
			|| !valid_redirs));
}

void	check_command(t_shell *shell, t_list **steps,
			t_exec *step, t_execflags *flags)
{
	if (check_invalid_path(step) == true)
	{
		if (!handle_invalid_path(shell, step, flags))
		{
			flags->action = -1;
			return ;
		}
		*steps = (*steps)->next;
		flags->action = 1;
		return ;
	}
	if (check_invalid_command(step, flags->valid_redirection) == true)
	{
		if (!flags->first_flag)
			flags->first_flag = true;
		if (!handle_invalid_cmd(shell, step, flags))
		{
			flags->action = -1;
			return ;
		}
		*steps = (*steps)->next;
		flags->action = 1;
		return ;
	}
	flags->action = 0;
}
