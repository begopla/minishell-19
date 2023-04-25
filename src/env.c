/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:52 by szubair           #+#    #+#             */
/*   Updated: 2023/04/15 20:10:39 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_env_var(const char *str, size_t *i)
{
	if (str[*i] == '\0')
		return (0);
	else if (str[*i] == '?')
		return (1);
	else if ((str[*i] == '\"' || str[*i] == '\''))
	{
		if (str[*i + 1] == '\0')
			return (0);
		else if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_')
			*i += 1;
		else
			return (1);
	}
	else if (!ft_isalnum(str[*i]) && str[*i] != '_')
		*i += 1;
	else
		return (1);
	if (str[*i] == '\0')
		return (0);
	return (-1);
}
