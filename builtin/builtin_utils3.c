/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:06:28 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 15:47:52 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_env_var(t_shell *shell, char **env_copy, char *to_look)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], to_look, ft_strlen(to_look)) != 0)
			env_copy[j++] = shell->env[i++];
		else
			ft_free2(&shell->env[i++]);
	}
}

void	remove_declared_env_var(t_shell *shell, char **env_copy, char *to_look)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (shell->declared_env[i] != NULL)
	{
		if (ft_strncmp(shell->declared_env[i], to_look,
				ft_strlen(to_look)) != 0)
			env_copy[j++] = shell->declared_env[i++];
		else
			ft_free2(&shell->declared_env[i++]);
	}
}
