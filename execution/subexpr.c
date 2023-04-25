/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subexpr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:45 by szubair           #+#    #+#             */
/*   Updated: 2023/04/24 14:19:23 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_and_fork_subexpr(t_shell *shell, t_exec *step,
	t_list **sub_steps)
{
	t_list		*sub_tokens;
	int			pid;
	int			success;

	sub_tokens = tokenize_the_input(shell, step->subexpr_line, &success);
	*sub_steps = ft_get_steps(sub_tokens, &success);
	ft_lstclear(&sub_tokens, free_token);
	ft_lstadd_back(&shell->steps_to_free, ft_lstnew(*sub_steps));
	pid = fork();
	if (pid == 0)
	{
		exec_cmds(shell, *sub_steps, 0, step->subexpr_line);
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		ft_close(&g_dupstdin);
		ft_free_array(shell->env);
		ft_free_array(shell->declared_env);
		ft_lstclear(&shell->heredoc_contents, free);
		ft_free2(&shell->fd);
		get_next_line(-1);
		free_steps(&shell->step);
		printf("Is it here I exit (9)\n");
		exit(shell->last_exit_code);
	}
	return (pid);
}
