/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mssg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:40 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:04:31 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_not_found(t_shell *shell, t_exec *step, bool *exit_flag)
{
	printf("minishell: %s: command not found\n", step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 127;
	shell->last_exit_code = step->exit_code;
}

void	cmd_is_dir(t_shell *shell, t_exec *step, bool *exit_flag)
{
	printf("minishell: %s: is a directory\n", step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 126;
	shell->last_exit_code = step->exit_code;
}

void	file_not_found(t_shell *shell, t_exec *step, bool *exit_flag)
{
	printf("minishell: %s: No such file or directory\n",
		step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 127;
	shell->last_exit_code = step->exit_code;
}

void	permission_denied(t_shell *shell, t_exec *step, bool *exit_flag)
{
	printf("minishell: %s: Permission denied\n", step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 126;
	shell->last_exit_code = step->exit_code;
}
