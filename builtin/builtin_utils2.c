/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:24:44 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 17:17:23 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_error(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
}

char	**resize_str_arr(char **old, size_t new_size)
{
	size_t	i;
	char	**new_arr;

	new_arr = ft_calloc(new_size + 1, sizeof(char *));
	if (new_arr == NULL)
		exit(1);
	i = 0;
	while (old[i] != NULL)
	{
		new_arr[i] = old[i];
		i++;
	}
	ft_free2(&old);
	return (new_arr);
}

bool	assign_val_to_env(t_shell *shell, char *to_look,
			char *key, char *key_val)
{
	int	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], to_look, ft_strlen(to_look)) == 0)
		{
			ft_free2(&to_look);
			ft_free2(&shell->env[i]);
			ft_free2(&key);
			shell->env[i] = key_val;
			return (false);
		}
		i++;
	}
	return (true);
}

void	print_the_export_env(char **val, char **key)
{
	if (*val[0] == '\0')
	{
		ft_free2(val);
		printf("declare -x %s\n", *key);
	}
	else
	{
		*val = join_and_free("=\"", *val, 2);
		*val = join_and_free(*val, "\"", 1);
		*key = join_and_free(*key, *val, 3);
		printf("declare -x %s\n", *key);
	}
}

void	run_export_with_args(char **args, t_shell *shell, bool *error)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (check_export_arg(args[i]) == false)
		{
			*error = true;
			export_error(args[i]);
		}
		else if (ft_strchr(args[i], '=') != NULL)
			update_env(shell, args[i]);
		else
		{
			unset_declared_var(shell, args[i]);
			update_declared_env(shell, args[i]);
		}
		i++;
	}
}
