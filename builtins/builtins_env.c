/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:27 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 11:21:20 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*get_env_key(char *env)
{
	int		len;
	char	*key;

	len = len_key(env);
	key = ft_substr(env, 0, len);
	return (key);
}

char	*get_env_value(char *env)
{
	int		len_k;
	int		len;
	char	*value;

	len_k = len_key(env);
	len = ft_strlen(env);
	value = ft_substr(env, len_k + 1, len - len_k);
	return (value);
}

void	init_env_ms(char **envp)
{
	int	i;

	i = 0;
	g_data.env_ms = NULL;
	while (envp[i])
	{
		ms_lstadd_back(&g_data.env_ms,
			ms_lstnew(get_env_key(envp[i]), get_env_value(envp[i]), true));
		i++;
	}
	lst_to_tab(g_data.env_ms);
}

void	ft_env(void)
{
	print_lst(g_data.env_ms);
}
