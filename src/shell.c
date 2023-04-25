/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:02:28 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/18 10:23:02 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*init_shell(char **envp, int *error)
{
	t_shell		*minishell;

	minishell = ft_calloc(sizeof(t_shell), 1);
	minishell->env = copy_env(envp);
	minishell->last_exit_code = 0;
	minishell->declared_env = NULL;
	minishell->steps_to_free = NULL;
	minishell->fd = ft_calloc(2, sizeof(int));
	if (!minishell->fd)
	{
		ft_free_array(minishell->env);
		exit(EXIT_FAILURE);
	}
	*error = 0;
	return (minishell);
}

static	int	subexpr_parse_error(t_list *tokens, t_list *steps)
{
	if (tokens)
		ft_lstclear(&tokens, free_token);
	if (steps)
		ft_lstclear(&steps, free_exec_step);
	return (1);
}

int	check_subexpr(t_shell *shell, t_list *shell_steps)
{
	t_exec		*step;
	t_list		*steps;
	t_list		*tokens;
	int			error;

	while (shell_steps != NULL)
	{
		step = shell_steps->content;
		if (step->subexpr_line)
		{
			tokens = tokenize_the_input(shell, step->subexpr_line, &error);
			if (error)
				return (subexpr_parse_error(tokens, NULL));
			steps = ft_get_steps(tokens, &error);
			ft_lstclear(&tokens, free_token);
			if (!steps || error || check_subexpr(shell, steps))
				return (subexpr_parse_error(NULL, steps));
			step = steps->content;
			if (step->subexpr_line  && !steps->next)
				return (subexpr_parse_error(NULL, steps));
			ft_lstclear(&steps, free_exec_step);
		}
		shell_steps = shell_steps->next;
	}
	return (0);
}


int	handle_get_steps_error(t_shell	*shell, int *error, char *line)
{
	if (*error || check_subexpr(shell,  shell->step))
	{
		shell->last_exit_code = 2; //2 exit code for sintax error or 127 for command not found
		printf("Parse error\n");
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		rl_on_new_line();
		ft_close(&g_dupstdin);
		ft_free(line); //is this also freed already?
		return (1);
	}
	return (0);
	
}
