/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_invalid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:02 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:06:57 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	handle_invalid_path(t_shell *shell, t_exec *step,
	t_execflags *flags)
{
	printf("minishell: %s: command not found\n",
		step->cmd->arg_arr[0]);
	flags->exit = true;
	step->exit_code = 127;
	shell->last_exit_code = step->exit_code;
	ft_close(&shell->fd[0]);
	shell->fd[0] = open("/dev/null", O_RDONLY);
	if (!flags->first_flag)
		flags->first_flag = true;
	return (true);
}

bool	handle_invalid_cmd(t_shell *shell, t_exec *step,
	t_execflags *flags)
{
	if (cmd_not_found_check(step, flags->valid_redirection))
		cmd_not_found(shell, step, &flags->exit);
	else if (is_dir(step->cmd->arg_arr[0]) && flags->valid_redirection)
		cmd_is_dir(shell, step, &flags->exit);
	else if (file_not_found_check(step, flags->valid_redirection))
		file_not_found(shell, step, &flags->exit);
	else if (permission_denied_check(step, flags->valid_redirection))
		permission_denied(shell, step, &flags->exit);
	ft_close(&shell->fd[0]);
	shell->fd[0] = open("/dev/null", O_RDONLY);
	return (true);
}
