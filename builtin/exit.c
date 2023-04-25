/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:57:33 by szubair           #+#    #+#             */
/*   Updated: 2023/04/08 19:53:33 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_exitcode(t_shell *shell, t_exec *command_block, const int exitcode)
{
	command_block->exit_code = exitcode;
	shell->last_exit_code = command_block->exit_code;
}

void	check_valid_args(t_shell *shell, t_exec *command_block, int i, int *j)
{
	if ((command_block->cmd->arg_arr[1] && command_block->cmd->arg_arr[1][i])
		|| (command_block->cmd->arg_arr[1] && command_block->cmd->arg_arr[1][0] == '\0'))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			command_block->cmd->arg_arr[1]);
		set_exitcode(shell, command_block, 255);
		*j = 1;
	}
	else if (command_block->cmd->arg_arr[1] && command_block->cmd->arg_arr[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		set_exitcode(shell, command_block, 1);
		*j = 1;
	}
}

void	ft_exit(t_exec *command_block, t_shell *shell, int child)
{
	int		i;
	int		j;
	int	check;

	i = 0;
	j = 0;
	check = 1;
	if (command_block->cmd->arg_arr[1] && (command_block->cmd->arg_arr[1][i] == '-'
		|| command_block->cmd->arg_arr[1][i] == '+'))
		i++;
	while (command_block->cmd->arg_arr[1] && command_block->cmd->arg_arr[1][i] >= '0'
			&& command_block->cmd->arg_arr[1][i] <= '9')
		i++;
	check_valid_args(shell, command_block, i, &j);
	if (!j && command_block->cmd->arg_arr[1] != NULL)
		set_exitcode(shell, command_block, ft_atox(command_block->cmd->arg_arr[1], &check));
	if (check == 0)
	{
		set_exitcode(shell, command_block, 255);
		printf("minishell: exit: %s: numeric argument required\n",
			command_block->cmd->arg_arr[1]);
	}
	if (!child)
		printf("exit\n");
}