/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:17:55 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 16:47:25 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	unset_error(char *arg)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
}

static bool	check_unset_arg(const char *arg)
{
	size_t	i;

	if (ft_strchr(arg, '=') != NULL || ft_isdigit(arg[0]))
		return (0);
	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (false);
}

void	unset_var(t_shell *shell, const char *var)
{
	size_t	i;
	int	found;
	char	*to_look;
	char	**env_copy;

	i = -1;
	found = false;
	to_look = ft_strjoin(var, "=");
	while (shell->env[++i] != NULL)
		if (ft_strncmp(shell->env[i], to_look, ft_strlen(to_look)) == 0)
			found = true;
	if (found == false)
	{
		ft_free2(&to_look);
		return ;
	}
	env_copy = ft_calloc(env_len(shell->env), sizeof(char *));
	remove_env_var(shell, env_copy, to_look);
	ft_free2(&shell->env);
	ft_free2(&to_look);
	shell->env = env_copy;
}

void	unset_declared_var(t_shell *shell, const char *var)
{
	size_t	i;
	int	found;
	char	*to_look;
	char	**env_copy;

	i = -1;
	found = false;
	if (shell->declared_env == NULL)
		return ;
	to_look = ft_strdup(var);
	while (shell->declared_env[++i] != NULL)
		if (ft_strncmp(shell->declared_env[i], to_look,
				ft_strlen(to_look)) == 0)
			found = true;
	if (found == false)
	{
		ft_free2(&to_look);
		return ;
	}
	env_copy = ft_calloc(env_len(shell->declared_env), sizeof(char *));
	remove_declared_env_var(shell, env_copy, to_look);
	ft_free2(&shell->declared_env);
	
	ft_free2(&to_look);
	shell->declared_env = env_copy;
}

void	ft_unset(t_shell *shell, t_exec *command_block)
{
	size_t	i;
	char	**args;
	int	error;

	error = false;
	args = command_block->cmd->arg_arr;
	i = 0;
	while (args[++i] != NULL)
	{
		if (check_unset_arg(args[i]) == false)
		{
			unset_error(args[i]);
			error = true;
		}
		else
		{
			unset_declared_var(shell, args[i]);
			unset_var(shell, args[i]);
		}
	}
	if (error)
		command_block->exit_code = 1;
	else
		command_block->exit_code = 0;
	shell->last_exit_code = command_block->exit_code;
}
