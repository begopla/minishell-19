/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:51:24 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/25 13:00:58 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_dupstdin;

void	free_exec_step_main(void *exec_step_ptr)
{
	t_exec	*exec_step;
	
	exec_step = exec_step_ptr;
	printf("Hello I am inside free_exec_step main\n");
	ft_lstclear(&exec_step->cmd->args, ft_free);
	//ft_lstclear(&exec_step->cmd->redirs, free_redir);
	//ft_free_array(exec_step->cmd->arg_arr);
	//ft_free(exec_step->cmd);
	ft_free(exec_step->subexpr_line);
	ft_free(exec_step);
}

void	free_steps_main(t_list **step_lists)
{
	t_list	*steps;
	t_list	*temp;

	printf("I am calling steps_to_free\n");

	while ((*step_lists) != NULL)
	{
		printf("I am getting inside free stps\n");
		steps = (*step_lists)->content;
		temp = (*step_lists)->next;
		ft_lstclear(&steps, free_exec_step_main);
		ft_free2(step_lists);
		ft_free(steps);
		(*step_lists) = temp;
		ft_free(temp);
	}
	*step_lists = NULL;

}

void	minishell_exec(t_shell *shell, char *line)
{
	if (shell->step != NULL)
		exec_cmds(shell, shell->step, 0, shell->line);
	ft_lstclear(&shell->tokens, free_token);
	ft_lstclear(&shell->heredoc_contents, free);
	free_steps_main(&shell->steps_to_free); //this was commented
	printf("I already free steps\n");
	rl_on_new_line();
	ft_free(line);
	ft_close(&g_dupstdin);
}

int main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	int		error;
	t_shell	*cmd;
	
	(void) argc;
	(void) argv;
	cmd = init_shell(envp, &error);
	while (1)
	{
		cmd_line = print_prompt(cmd);
		if(add_to_history(cmd_line) == FALSE)
			continue;
		error = TRUE;
		cmd->tokens = tokenize_the_input(cmd, cmd_line, &error);
		if (ft_is_token_error(cmd, cmd_line, &error))
			continue;
		cmd->step = ft_get_steps(cmd->tokens, &error);
		if (handle_get_steps_error(cmd, &error, cmd_line))
			continue;
		ft_lstadd_back(&cmd->steps_to_free, cmd->step);
		run_heredocs(cmd);
		if (heredoc_ctrl_c(cmd, cmd_line) == false)
			continue ;

		minishell_exec(cmd, cmd_line);		
	}
	printf("when do I exit from loop");
	exit(EXIT_SUCCESS);
	return(0);
}


