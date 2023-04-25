/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:27 by szubair           #+#    #+#             */
/*   Updated: 2023/04/17 13:50:43 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_heredocs(t_shell *shell)
{
	signal(SIGINT, heredoc_sig);
	signal(SIGQUIT, heredoc_sig);
	shell->heredoc_contents = run_here_docs(shell, shell->step);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

bool	contains_env_var(char *str)
{
	size_t	i;
	bool	in_s_quotes;
	bool	in_d_quotes;
	int		ret;

	i = 0;
	in_s_quotes = false;
	in_d_quotes = false;
	while (str[i] != '\0')
	{
		set_which_quotes(str, i, &in_s_quotes, &in_d_quotes);
		if (str[i] == '$' && in_s_quotes == false)
		{
			i++;
			ret = is_env_var(str, &i);
			if (ret == 0)
				return (false);
			if (ret == 1)
				return (false);
			i++;
		}
		else
			i++;
	}
	return (false);
}

static char	*read_from_stdin(t_shell *shell, char *limiter)
{
	char	*buff;
	char	*line;

	buff = ft_calloc(1, sizeof(char));
	line = NULL;
	if (buff == NULL)
		return (NULL);
	limiter = join_and_free(limiter, "\n", 1);
	while (1)
	{
		if (g_dupstdin != -1)
			ft_putstr_fd("> ", 1);
		line = get_next_line(g_dupstdin);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			// free_redir(redirec);
			break ;
		}
		while (contains_env_var(line) == true)
			line = expand_env(shell, line);
		buff = join_and_free(buff, line, 3);
	}
	ft_free2(&limiter);
	ft_free2(&line);
	get_next_line(-1);
	return (buff);
}

static void	run_heredoc(t_shell *shell, t_exec *step,
	t_list **heredocs)
{
	t_list	*redirs;
	t_redir	*redir;
	char	*contents;

	contents = NULL;
	if (step->cmd->redirs != NULL)
	{
		redirs = step->cmd->redirs;
		while (redirs != NULL)
		{
			redir = redirs->content;
			if (redir->type == HEREDOC)
				contents = read_from_stdin(shell, redir->limiter);
			redirs = redirs->next;
		}
		if (contents != NULL)
		{
			ft_lstadd_back(heredocs, ft_lstnew(ft_strdup(contents)));
			ft_free(contents);
		}
	}
}

t_list	*run_here_docs(t_shell *shell, t_list *steps)
{
	t_list		*heredocs;
	t_exec		*step;
	t_list		*tokens;
	t_list		*substeps;
	int			success;

	heredocs = NULL;
	while (steps != NULL)
	{
		step = steps->content;
		if (step->subexpr_line != NULL)
		{
			tokens = tokenize_the_input(shell, step->subexpr_line, &success);
			substeps = ft_get_steps(tokens, &success);
			ft_lstclear(&tokens, free_token);
			ft_lstadd_back(&heredocs, run_here_docs(shell, substeps));
			ft_lstclear(&substeps, free_exec_step);
			steps = steps->next;
			continue ;
		}
		run_heredoc(shell, step, &heredocs);
		steps = steps->next;
	}
	return (heredocs);
}
