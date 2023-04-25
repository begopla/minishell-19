/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:24:48 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 19:59:55 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	move_to_home(t_shell *shell, t_exec *step, char **env, char *home)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		oldpwd = ft_getenv(shell, "PWD");
		ft_free2(&home);
		return ;
	}
	if (!chdir(home) && ft_strlen(oldpwd))
	{
		update_pwd(env, shell);
		update_oldpwd(shell, env, oldpwd);
		step->exit_code = 0;
	}
	ft_free2(&oldpwd);
	ft_free2(&home);
}

size_t	env_len(char **env)
{
	size_t	len;

	len = 0;
	while (env[len] != NULL)
		len++;
	return (len);
}
