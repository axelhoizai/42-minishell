/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 21:52:26 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_hostname(void)
{
	int		fd;
	char	*hostname;
	char	*tmp;
	char	**split;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("minishell"));
	tmp = get_next_line(fd);
	if (tmp && ft_strchr(tmp, '\n'))
		tmp[ft_strlen(tmp) - 1] = '\0';
	close(fd);
	split = ft_split(tmp, '.');
	free_var(tmp);
	if (!split || !split[0])
	{
		free_tab(split);
		return (ft_strdup("minishell"));
	}
	hostname = ft_strdup(split[0]);
	free_tab(split);
	return (hostname);
}

static char	*ft_get_currentpath(t_env_ms *lst, char *currentpath)
{
	char		*home;
	char		*result;
	t_env_ms	*tmp;
	char		*tmp_env_key;

	home = NULL;
	tmp_env_key = get_envkey("HOME");
	if (tmp_env_key)
	{
		tmp = ms_find(lst, tmp_env_key);
		if (tmp && tmp->value)
			home = tmp->value;
		free_var(tmp_env_key);
	}
	if (home && ft_strncmp(currentpath, home, ft_strlen(home)) == 0)
	{
		result = ft_safe_malloc(ft_strlen(currentpath) - ft_strlen(home) + 2);
		if (!result)
			return (free_var(currentpath), NULL);
		result[0] = '~';
		ft_strcpy(result + 1, currentpath + ft_strlen(home));
		free_var(currentpath);
		return (result);
	}
	return (currentpath);
}

static char	*ft_get_username(t_env_ms *lst)
{
	char		*username;
	t_env_ms	*tmp;
	char		*tmp_env_key;
	char		*tmp_username;

	username = "minishell";
	tmp_env_key = get_envkey("USER");
	if (tmp_env_key)
	{
		tmp = ms_find(lst, tmp_env_key);
		if (tmp && tmp->value)
			username = tmp->value;
		free_var(tmp_env_key);
	}
	tmp_username = ft_strjoin(username, "@");
	return (tmp_username);
}

static char	*color_prompt(char *prompt, char *current_path)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*color_prompt;
	char	*colorcurrentpath;

	color_prompt = NULL;
	tmp1 = ft_strjoin("\e[1;32m", prompt);
	tmp2 = ft_strjoin(tmp1, "\e[m");
	free_var(tmp1);
	tmp3 = ft_strjoin(tmp2, ":");
	free_var(tmp2);
	tmp1 = ft_strjoin("\e[1;34m", current_path);
	tmp2 = ft_strjoin(tmp1, "\e[m");
	colorcurrentpath = ft_strjoin(tmp2, "$ ");
	free_var(tmp1);
	free_var(tmp2);
	free_var(color_prompt);
	color_prompt = ft_strjoin(tmp3, colorcurrentpath);
	free_var(colorcurrentpath);
	free_var(tmp3);
	return (color_prompt);
}

char	*get_prompt(t_env_ms *lst)
{
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*tmp2;
	char	*current_path;

	prompt = NULL;
	username = ft_get_username(lst);
	hostname = ft_get_hostname();
	tmp2 = ft_strjoin(username, hostname);
	current_path = getcwd(NULL, 0);
	update_pwd();
	if (!current_path)
		current_path = ft_strdup("~");
	current_path = ft_get_currentpath(lst, current_path);
	prompt = color_prompt(tmp2, current_path);
	free_var(tmp2);
	free_var(username);
	if (ft_strncmp(hostname, "minishell", 9) != 0)
		free_var(hostname);
	free_var(current_path);
	return (prompt);
}
