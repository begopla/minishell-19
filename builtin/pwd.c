/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:57:40 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 15:49:01 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_exec *command_block, t_shell *shell)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		dir = ft_getenv(shell, "PWD");
	if (!dir)
		return ;
	printf("%s\n", dir);
	ft_free2(&dir);
	command_block->exit_code = 0;
	shell->last_exit_code = command_block->exit_code;
}
