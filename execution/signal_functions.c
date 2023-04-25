/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:35 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:08:43 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_interactive(int sig)
{
	int	ret;

	ret = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT && ret == -1)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_close(&g_dupstdin);
	}
}

void	sigint(int sig)
{
	int	ret;

	ret = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT)
	{
		if (ret == -1)
		{
			write(2, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
	}
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_close(&g_dupstdin);
		get_next_line(-1);
		rl_on_new_line();
		printf("\n");
	}
}
