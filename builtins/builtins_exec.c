/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/31 16:17:19 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute(char *cmd, t_data *data)
{
	char	**cmd_args;
	char	*cmd_path;

	if (ft_strstr(cmd, "./"))
		script_checker(cmd);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		free_tab(cmd_args);
		print_error("minishell: Invalid command", NULL, CMD_NOT_FOUND);
		return ;
	}
	cmd_path = get_path(cmd_args[0], data->my_envp);
	if (ft_strstr(cmd_args[0], "./"))
		cmd_path = cmd_args[0];
	if (execve(cmd_path, cmd_args, data->my_envp) == -1)
	{
		free_tab(data->my_envp);
		ms_lstclear(&data->env_ms);
		free_tab(cmd_args);
		ft_print_error(ft_strtok(cmd, " "), NULL, "command not found");
		free(cmd);
		data->exit_code = CMD_NOT_FOUND;
		exit(CMD_NOT_FOUND);
	}
}

static char	*parse_cmd(char **argv, char *cmd)
{
	char	*tmp;

	if (argv && argv[0] && ft_strcmp(argv[0], "<") == 0)
	{
		tmp = ft_strjoin(argv[2], " ");
		free (cmd);
		cmd = ft_strjoin(tmp, argv[1]);
		free(tmp);
		return (cmd);
	}
	return (ft_strdup(cmd));
}

void	exec(char **argv, t_data *data)
{
	int		status;
	pid_t	pid[2];
	char	*tmp;
	char	*cmd;

	cmd = join_argv(argv);
	if (cmd)
	{
		tmp = parse_cmd(argv, cmd);
		free_tab(argv);
		free (cmd);
		pid[0] = fork();
		if (pid[0] == -1)
			exit(1);
		if (pid[0] == 0)
			execute(tmp, data);
		free(tmp);
		waitpid(pid[0], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) >= 0)
			data->exit_code = WEXITSTATUS(status);
	}
}
