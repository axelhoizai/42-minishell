/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:27 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/03 15:51:30 by ahoizai          ###   ########.fr       */
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

char	*get_envkey(char *env)
{
	int		len;
	char	*key;

	len = len_key(env);
	key = ft_substr(env, 0, len);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_envval(char *env)
{
	int		len_k;
	int		len;
	char	*value;

	len_k = len_key(env);
	len = ft_strlen(env);
	value = ft_substr(env, len_k + 1, len - len_k);
	return (value);
}

void	init_env_ms(char **envp, t_data *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	data->env_ms = NULL;
	while (envp[i])
	{
		key = get_envkey(envp[i]);
		value = get_envval(envp[i]);
		ms_lstadd_back(&data->env_ms, ms_lstnew(key, value, true));
		i++;
	}
	lst_to_tab(data->env_ms, data);
}

void	ft_env(t_data *data, t_pipeline *pip)
{
	(void)pip;
	print_lst(data->env_ms);
	// free_pipeline(pip);
}
