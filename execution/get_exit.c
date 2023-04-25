/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:56 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:06:52 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_exit(t_list *exec_steps, t_exec *step, t_execflags *flags)
{
	if (!flags->exit && !WIFEXITED(flags->w_status)
		&& WIFSIGNALED(flags->w_status))
	{
		if (WTERMSIG(flags->w_status) == SIGINT)
			step->exit_code = 130;
		if (WTERMSIG(flags->w_status) == SIGQUIT)
		{
			printf("Quit\n");
			step->exit_code = 131;
		}
		return (step->exit_code);
	}
	if (!flags->exit)
	{
		if (!(((t_exec *)exec_steps->content)->pipe_next == false
				&& parent_builtin(exec_steps->content)))
		{
			step->exit_code = WEXITSTATUS(flags->w_status);
		}
	}
	return (step->exit_code);
}
