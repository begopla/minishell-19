/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:14 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:07:43 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_valid_redir(t_exec *step)
{
	t_list	*redir;
	t_redir	*redir_file;

	if (step->cmd == NULL)
		return (TRUE);
	redir = step->cmd->redirs;
	while (redir)
	{
		redir_file = redir->content;
		if (check_input_redir(redir_file) == FALSE)
			return (FALSE);
		else if (check_output_redir(redir_file) == FALSE)
			return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}

static int	exec_outredir(t_exec *step)
{
	t_list	*redir;
	t_redir	*redir_file;
	int		out_fd;
	int		check;

	out_fd = -1;
	if (step->cmd == NULL)
		return (out_fd);
	redir = step->cmd->redirs;
	while (redir)
	{
		redir_file = redir->content;
		check = check_access_for_redir(redir_file, &redir);
		if (check == 1)
			break ;
		else if (check == 2)
			continue ;
		if (check_redir_file_exist(redir_file, &out_fd) == FALSE)
			return (out_fd);
		else
			if (create_redir_file(redir_file, &out_fd) == FALSE)
				return (-2);
		redir = redir->next;
	}
	return (out_fd);
}

bool	open_redirs(t_shell *shell, t_exec *step,
	bool *exit_flag, int *out_fd)
{
	bool	valid_redirs;

	valid_redirs = check_valid_redir(step);
	if (valid_redirs == false)
	{
		*exit_flag = true;
		step->exit_code = 1;
		shell->last_exit_code = step->exit_code;
	}
	*out_fd = exec_outredir(step);
	if (*out_fd == -2)
	{
		valid_redirs = false;
		*exit_flag = true;
		step->exit_code = 1;
		*out_fd = -1;
		shell->last_exit_code = step->exit_code;
	}
	return (valid_redirs);
}

t_redir	*last_inredir(t_list *in_redir)
{
	t_redir	*last;
	t_redir	*current_redir;

	last = NULL;
	while (in_redir)
	{
		current_redir = in_redir->content;
		if (current_redir->type == INPUT_REDIR
			|| current_redir->type == HEREDOC)
			last = current_redir;
		in_redir = in_redir->next;
	}
	return (last);
}
