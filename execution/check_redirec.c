/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:22 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 19:14:24 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_input_redir(t_redir	*redir_file)
{
	if (redir_file->type == INPUT_REDIR)
	{
		if (access(redir_file->file, F_OK) == -1)
		{
			printf("minishell: %s: No such file or directory\n",
				redir_file->file);
			return (false);
		}
		if (access(redir_file->file, R_OK) == -1)
		{
			printf("minishell: %s: Permission denied\n",
				redir_file->file);
			return (false);
		}
	}
	return (true);
}

bool	check_output_redir(t_redir	*redir_file)
{
	if (redir_file->type == OUTPUT_REDIR || redir_file->type == APPEND)
	{
		if ((access(redir_file->file, F_OK) != -1
				&& access(redir_file->file, W_OK) == -1)
			|| is_dir(redir_file->file))
		{
			printf("minishell: %s: Permission denied\n",
				redir_file->file);
			return (false);
		}
	}
	return (true);
}

bool	check_redir_file_exist(t_redir *redir_file, int *out_fd)
{
	if (access(redir_file->file, W_OK) == 0)
	{
		ft_close(out_fd);
		if (redir_file->type == APPEND)
			*out_fd = open(redir_file->file, O_WRONLY | O_APPEND);
		else
			*out_fd = open(redir_file->file, O_WRONLY | O_TRUNC);
		if (*out_fd == -1)
			printf("minishell: %s: failed to open\n", redir_file->file);
		return (true);
	}
	else if ((access(redir_file->file, F_OK) != -1
			&& access(redir_file->file, W_OK) == -1)
		|| is_dir(redir_file->file))
		return (false);
	return (true);
}

int	check_access_for_redir(t_redir *redir_file, t_list **redir)
{
	if (redir_file->type == INPUT_REDIR)
	{
		if (access(redir_file->file, R_OK) == -1)
			return (1);
	}
	else if (redir_file->type == OUTPUT_REDIR || redir_file->type == APPEND)
	{
		if ((access(redir_file->file, F_OK) != -1
				&& access(redir_file->file, W_OK) == -1)
			|| is_dir(redir_file->file))
			return (1);
	}
	if (redir_file->type == INPUT_REDIR || redir_file->type == HEREDOC)
	{
		*redir = (*redir)->next;
		return (2);
	}
	return (0);
}

bool	create_redir_file(t_redir *redir_file, int *out_fd)
{
	ft_close(out_fd);
	if (redir_file->type == APPEND)
		*out_fd = open(redir_file->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*out_fd = open(redir_file->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_fd == -1)
	{
		printf("minishell: %s: No such file or directory\n",
			redir_file->file);
		return (false);
	}
	return (true);
}
