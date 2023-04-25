/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:57:50 by szubair           #+#    #+#             */
/*   Updated: 2023/04/07 14:38:11 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_shell *command_block, t_exec *step)
{
	size_t	i;

	i = 0;
	if (step->cmd->arg_arr[1] != NULL)
	{
		step->exit_code = 1;
		command_block->last_exit_code = step->exit_code;
		return ;
	}
	while (command_block->env[i] != NULL)
	{
		printf("%s\n", command_block->env[i]);
		i++;
	}
	step->exit_code = 0;
	command_block->last_exit_code = step->exit_code;
}
