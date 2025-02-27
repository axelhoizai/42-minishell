/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/27 13:55:55 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_dir(t_data	*data)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	printf("%s\n", currentpath);
	free(currentpath);
	data->exit_code = 0;
}

static void	var_export(t_data *data, char *var)
{
	char	**ex;

	ex = ft_safe_malloc(sizeof(char *) * 3);
	if (!ex)
	{
		free(var);
		return ;
	}
	ex[0] = ft_strdup("export");
	ex[1] = ft_strdup(var);
	ex[2] = NULL;
	if (!ex[0])
	{
		free(var);
		free(ex);
		return ;
	}
	ft_export(ex, data);
	free_tab(ex);
	free(var);
}

void	update_pwd(void)
{
	t_data	*data;
	char	*tmp;
	char	*tmp2;

	data = get_data(NULL);
	if (!data)
		return ;
	tmp2 = getcwd(NULL, 0);
	if (ft_strcmp(tmp2, data->pwd) != 0)
	{
		free(data->pwd);
		data->pwd = getcwd(NULL, 0);
		if (!data->pwd)
			return ;
		tmp = ft_strjoin("PWD=", data->pwd);
		if (!tmp)
			return ;
		else
			var_export(data, tmp);
	}
	free(tmp2);
}

void	update_oldpwd(void)
{
	char	*tmp;
	t_data	*data;

	data = get_data(NULL);
	if (!data)
		return ;
	free(data->oldpwd);
	data->oldpwd = ft_strdup(data->pwd);
	if (!data->oldpwd)
		return ;
	tmp = ft_strjoin("OLDPWD=", data->oldpwd);
	if (!tmp)
		return ;
	else
		var_export(data, tmp);
	data->exit_code = 0;
}
