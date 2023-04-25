/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:20 by szubair           #+#    #+#             */
/*   Updated: 2023/04/24 17:15:15 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*run_parent_builtin(t_exec *step, t_shell *shell, int *fd)
{
	int	x;

	run_builtin(step, shell, FALSE);
	if (ft_strcmp(step->cmd->arg_arr[0], "exit") == 0)
	{
		x = 0;
		if (step->cmd->arg_arr)
		{
			ft_lstclear(&shell->tokens, free_token);
			free_steps(&shell->steps_to_free);
			ft_free_array(shell->env);
			ft_free_array(shell->declared_env);
			ft_lstclear(&shell->heredoc_contents, free);
			ft_close(&g_dupstdin);
			ft_free2(&shell->fd);
			x = shell->last_exit_code;
			printf("Is it here I exit (10)\n");
			free(shell);
		}
		exit(x);
	}
	return (fd);
}

int	run_child_builtin(t_shell *shell, t_exec *step, int *fds,
	int *heredoc_fds)
{
	int	exit_code;

	run_builtin(step, shell, TRUE);
	ft_close(&fds[1]);
	ft_close(&fds[0]);
	ft_close(&heredoc_fds[0]);
	ft_close(&heredoc_fds[1]);
	ft_close(&g_dupstdin);
	exit_code = step->exit_code;
	printf("Is it here I exit (3)\n");
	ft_lstclear(&shell->tokens, free_token);
	ft_free(shell->step);
	ft_free_array(shell->env);
	ft_free_array(shell->declared_env);
	ft_lstclear(&shell->heredoc_contents, free);
	ft_free2(&fds);
	free(shell);
	return (exit_code);
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_void;
	if (!cmd)
		return ;
	ft_lstclear(&cmd->args, ft_free);
	ft_free_array(cmd->arg_arr);
	ft_lstclear(&cmd->redirs, free_redir);
	ft_free(cmd);
}


int	run_child_builtin2(t_shell *shell, t_exec *step, int *fds,
	int *heredoc_fds)
{
	int	exit_code;

	run_builtin(step, shell, TRUE);
	ft_close(&fds[1]);
	ft_close(&fds[0]);
	ft_close(&heredoc_fds[0]);
	ft_close(&heredoc_fds[1]);
	ft_close(&g_dupstdin);
	exit_code = step->exit_code;
	printf("Is it here I exit (4)\n");
	ft_free_array(shell->env);
	ft_free_array(shell->declared_env);
	ft_lstclear(&shell->tokens, free_token);
	ft_lstclear(&shell->heredoc_contents, free);
	
	while(shell->step)
	{
		t_exec	*exec_step = shell->step->content;

		free_cmd(exec_step->cmd);
		if (exec_step->subexpr_line)
			ft_free(exec_step->subexpr_line);
		ft_free(exec_step);
		shell->step = shell->step->next;
	}

	ft_free(shell->step);
	ft_free2(&shell->fd);
	ft_free(shell);
	return (exit_code);
}
