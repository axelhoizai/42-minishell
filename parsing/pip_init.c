/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:06:04 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 18:56:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipeline	*init_pipeline(void)
{
	t_pipeline	*pip;

	pip = ft_calloc(1, sizeof(t_pipeline));
	if (!pip)
		return (NULL);
	pip->cmds = NULL;
	pip->pipe_cnt = 0;
	pip->pid = NULL;
	return (pip);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->arg_cnt = 0;
	cmd->fd_in = -2;
	cmd->in_error = 0;
	cmd->input_file = NULL;
	cmd->fd_out = -2;
	cmd->out_error = 0;
	cmd->output_file = NULL;
	cmd->limiter = NULL;
	cmd->trunc = 0;
	cmd->append = 0;
	cmd->heredoc = 0;
	return (cmd);
}

int	*init_pid(t_pipeline *pip)
{
	int	*pid;
	
	pid = ft_calloc(pip->pipe_cnt + 1, sizeof (int *));
	if (!pid)
		return (NULL);
	return (pid);
}

char	**add_to_tab(char **tab, const char *arg)
{
	char	**new_tab;
	int		size;
	int		i;

	size = 0;
	while (tab && tab[size])
		size++;
	new_tab = ft_calloc(size + 2, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(arg);
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}

void	add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd)
{
	t_command	**new_cmds;
	int			size;
	int			i;

	size = 0;
	while (pipeline->cmds && pipeline->cmds[size])
		size++;
	new_cmds = ft_calloc(size + 2, sizeof(t_command *));
	if (!new_cmds)
		return ;
	i = 0;
	while (pipeline->cmds && pipeline->cmds[i])
	{
		new_cmds[i] = pipeline->cmds[i];
		i++;
	}
	new_cmds[i] = cmd;
	new_cmds[i + 1] = NULL;
	free(pipeline->cmds);
	pipeline->cmds = new_cmds;
}
