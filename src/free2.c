#include "../include/minishell.h"

void	free_redir(void *redir_ptr)
{
	t_redir	*redir;

	redir = redir_ptr;
	ft_free(redir->file);
	ft_free(redir->limiter);
	ft_free(redir);
}

// void	free_exec_step(void *exec_step_ptr)
// {
// 	t_exec	*exec_step;
// 	size_t		i;

	
// 	exec_step = exec_step_ptr;
// 	printf("Hello I am inside free_exec_step\n");
// 	if (exec_step->cmd)
// 	{
// 		printf("I have cmd data to free\n");
// 		ft_lstclear(&exec_step->cmd->redirs, free_redir);
// 		ft_lstclear(&exec_step->cmd->args, ft_free);
// 		i = 0;
// 		while (exec_step->cmd->arg_arr[i] != NULL)
// 		{
// 			ft_free(exec_step->cmd->arg_arr[i]);
// 			i++;
// 		}
// 		ft_free(exec_step->cmd->arg_arr);
// 		ft_free(exec_step->cmd);
// 	}
// 	else
// 		ft_free(exec_step->cmd);
// 	ft_free(exec_step->subexpr_line);
// 	ft_free(exec_step);
// }

void	free_exec_step(void *exec_step_ptr)
{
	t_exec	*exec_step;
	
	exec_step = exec_step_ptr;
	printf("Hello I am inside free_exec_step\n");
	//ft_lstclear(&exec_step->cmd->redirs, free_redir);
	//ft_lstclear(&exec_step->cmd->args, ft_free);
	ft_free_array(exec_step->cmd->arg_arr);
	ft_free(exec_step->cmd);
	ft_free(exec_step->subexpr_line);
	ft_free(exec_step);
}

void	free_steps(t_list **step_lists)
{
	t_list	*steps;
	t_list	*temp;

	printf("I am calling steps_to_free\n");

	while ((*step_lists) != NULL)
	{
		printf("I am getting inside free stps\n");
		steps = (*step_lists)->content;
		temp = (*step_lists)->next;
		ft_lstclear(&steps, free_exec_step);
		ft_free2(step_lists);
		ft_free(steps);
		(*step_lists) = temp;
		ft_free(temp);
	}
	*step_lists = NULL;

}
