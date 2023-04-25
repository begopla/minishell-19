/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:37:16 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/14 11:54:58 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	print_data_ex(t_list *steps)
{
	t_exec	*ex_step;
	t_cmd	*cmd;
	t_list	*re_files_list;
	t_redir	*file;
	t_list	*args_list;
	//int 	i;

	//char	**arg_array;
	
	while (steps)
	{
		ex_step = steps->content;
		cmd = ex_step->cmd;
		re_files_list = cmd->redirs;
		args_list = cmd->args;
		while (args_list)
		{
			char *args_c= args_list->content;
			printf("New step: %s\n", args_c);
			args_list = args_list->next;
		}

		// ***** SAME DATA BUT STORED IN char **arg_arr ******
		
		//arg_array = cmd->arg_arr;
		// printf("Printing all values from arg_array:\n");
		// i = 0;
		// while(arg_array[i])
		// {
		// 	printf("Array %d: %s\n", i, arg_array[i]);
		// 	i++;
		// }
		// ******************************************//
		
		
		if (ex_step->pipe_next)
			printf("The next step is a PIPE\n");
		while(re_files_list)
		{
			file = re_files_list->content;
			if(file->type == OUTPUT_REDIR)
				printf("Output redirection to %s\n", file->file);
			else if(file->type == APPEND)
				printf("Append redirection to %s\n", file->file);
			else if(file->type == INPUT_REDIR)
	 			printf("Input redirection from %s\n", file->file);
			else if (file->type == HEREDOC)
	 			printf("Heredoc redir. The limiter value for HEREDOC is %s\n", file->limiter);
			re_files_list = re_files_list->next;
		}
		steps = steps->next;
	}
	
}

void	count_num_pipes(t_list *steps)
{
	int 	num_pipes;
	t_exec	*ex_step;

	num_pipes = 0;
	while (steps)
	{
		ex_step = steps->content;
		if (ex_step->pipe_next)
				num_pipes += 1;;
		steps = steps->next;
	}
	printf("The total num of pipes is: %d\n", num_pipes);
}
