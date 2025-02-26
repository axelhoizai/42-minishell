/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:19:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 13:26:09 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_var(void *var)
{
	if (!var)
		return ;
	if (var)
	{
		free(var);
		var = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_term(t_data *data)
{
	if (data->term)
	{
		free(data->term);
		data->term = NULL;
	}
}

void	free_execute(t_pipeline *pip, t_data *data, char *cmd_path)
{
	free(cmd_path);
	ms_lstclear(&data->env_ms);
	free_tab(data->my_envp);
	free_term(data);
	free_pipeline(pip);
	free(data->pwd);
	free(data->oldpwd);
}
