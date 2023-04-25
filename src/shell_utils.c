/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:11:04 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/14 11:41:43 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **envp)
{
	size_t	i;
	char	**new_str;

	i = 0;
	while (envp[i])
		i++;
	new_str = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new_str[i] = ft_strdup(envp[i]);
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}
