/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 17:45:04 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_hostname(void)
{
	int		fd;
	char	*hostname;
	char	*tmp;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return ("minishell");
	tmp = get_next_line(fd);
	if (ft_strchr(tmp, '\n'))
		tmp[strlen(tmp) - 1] = '\0';
	close(fd);
	hostname = ft_strtok(tmp, ".");
	if (!hostname)
		hostname = "minishell";
	ft_strtok(NULL, ".");
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
		free(tmp_env_key);
	}
	if (home && strncmp(currentpath, home, strlen(home)) == 0)
	{
		result = (char *)malloc(strlen(currentpath) - strlen(home) + 2);
		if (!result)
			return (free(currentpath) ,NULL);
		result[0] = '~';
		strcpy(result + 1, currentpath + strlen(home));
		free(currentpath);
		return (result);
	}
	return (currentpath);
}

static char	*ft_get_username(t_env_ms *lst)
{
	char		*username;
	t_env_ms	*tmp;
	char		*tmp_env_key;

	username = "minishell";
	tmp_env_key = get_envkey("USER");
	if (tmp_env_key)
	{
		tmp = ms_find(lst, tmp_env_key);
		if (tmp && tmp->value)
			username = tmp->value;
		free(tmp_env_key);
	}
	username = ft_strjoin(username, "@");
	return (username);
}

static char	*color_prompt(char *prompt, char *current_path)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*color_prompt;
	char	*colorcurrentpath;

	tmp1 = ft_strjoin("\e[1;32m", prompt);
	tmp2 = ft_strjoin(tmp1, "\e[m");
	free(tmp1);
	tmp3 = ft_strjoin(tmp2, ":");
	free(tmp2);
	tmp1 = ft_strjoin("\e[1;34m", current_path);
	tmp2 = ft_strjoin(tmp1, "\e[m");
	colorcurrentpath = ft_strjoin(tmp2, "$ ");
	free(tmp1);
	free(tmp2);
	color_prompt = ft_strjoin(tmp3, colorcurrentpath);
	free(tmp3);
	free(colorcurrentpath);
	return (color_prompt);
}

char	*get_prompt(t_env_ms *lst)
{
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*tmp2;
	char	*current_path;

	username = ft_get_username(lst);
	hostname = ft_get_hostname();
	tmp2 = ft_strjoin(username, hostname);
	current_path = getcwd(NULL, 0);
	if (!current_path)
		current_path = ft_strdup("~");
	current_path = ft_get_currentpath(lst, current_path);
	prompt = color_prompt(tmp2, current_path);
	free(tmp2);
	free(username);
	if (ft_strncmp(hostname, "minishell", 9) != 0)
		free(hostname);
	free(current_path);
	return (prompt);
}
