/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:18:23 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/18 10:23:33 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *line, size_t i)
{
	if ((line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '>' && line[i + 1] != '>')
		|| (line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '<' && line[i + 1] != '>')
		|| (line[i] == '|' && line[i + 1] != '|')
	)
		return (1);
	return (0);
}

void	*throw_error(char *msg)
{
	if (msg)
		printf("%s", msg);
	return (NULL);
}

void	ft_is_token_type(t_token_type *type, char *line, size_t *i)
{
	if (line[*i] == '|' && line[*i + 1] != '|')
		*type = PIPE;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		*type = APPEND;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		*type = HEREDOC;
	else if (line[*i] == '>' && line[*i + 1] != '>')
		*type = OUTPUT_REDIR;
	else
		*type = INPUT_REDIR;
}

int	ft_is_token_error(t_shell *minishell, char *line, int *error)
{
	(void) line;
	if (*error)
	{
		minishell->last_exit_code = 2; //or 127 for command not found
		ft_lstclear(&minishell->tokens, free_token);
		ft_close(&g_dupstdin);
		ft_free(line); //This memory was already freed here -> giving an free error
		return (1);
	}
	return (0);
}

int	last_was_heredoc_line(char *line, size_t len)
{
	if (line[len - 3] != '<' && line[len - 2] != '<')
		return (1);
	return (0);
}
