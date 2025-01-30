/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:56:03 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 19:24:32 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
#include "../minishell.h"

char	*get_env_path(char **envp)
{
	char	*env_path;
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	env_path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			tmp = ft_split(ft_strnstr(envp[i], "PATH=", 5), '=');
			if (tmp)
				env_path = ft_strdup(tmp[1]);
		}
		i++;
	}
	free_tab(tmp);
	return (env_path);
}

char	*get_path(char *cmd, char **envp)
{
	char	**all_path;
	int		i;
	char	*env_path;
	char	*cmd_parsed;
	char	*cmd_path;

	i = 0;
	cmd_parsed = get_cmd(cmd);
	if (access(cmd_parsed, F_OK) != -1)
		return (cmd_parsed);
	env_path = get_env_path(envp);
	all_path = ft_split(env_path, ':');
	while (env_path != NULL && all_path[i])
	{
		cmd_path = ft_strjoin(all_path[i], cmd_parsed);
		if (access(cmd_path, F_OK) != -1)
			return (free_tab(all_path), free(cmd_parsed), cmd_path);
		free(cmd_path);
		i++;
	}
	free(env_path);
	free_tab(all_path);
	free(cmd_parsed);
	return ("-1");
}

char	*get_cmd(char *cmd)
{
	char	**tmp;
	char	*cmd_parsed;

	if (ft_strchr(cmd, ' '))
	{
		tmp = ft_split(cmd, ' ');
		cmd_parsed = ft_strjoin("/", tmp[0]);
		free_tab(tmp);
	}
	else
		cmd_parsed = ft_strjoin("/", cmd);
	return (cmd_parsed);
}
