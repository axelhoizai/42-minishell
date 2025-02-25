/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/25 03:10:31 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtins(t_command *cmd, t_pipeline *pip, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->arg_cnt, cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		change_dir(cmd->arg_cnt, cmd->args, pip, data);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		get_dir(data, pip);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd->args, data);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd->args, data);
	else if (ft_strcmp(cmd->args[0], "env") == 0 && cmd->args[1])
		ft_print_error(NULL, NULL, "Use \'env\' with no options or arguments");
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		handle_exit(cmd, pip, data);
	else if (ft_strcmp(cmd->args[0], "clear") == 0)
		printf("\033[3J\033[H\033[J");
}

static void	fds_dup(int *fd_std, t_pipeline *pip, t_data *data)
{
	if (pip->cmds[0]->fd_out > -1)
	{
		*fd_std = dup(STDOUT_FILENO);
		dup2(pip->cmds[0]->fd_out, STDOUT_FILENO);
		close(pip->cmds[0]->fd_out);
	}
	if (pip->cmds[0]->out_error == 0 && pip->cmds[0]->in_error == 0)
		handle_builtins(pip->cmds[0], pip, data);
	if (pip->cmds[0]->output_file)
	{
		dup2(*fd_std, STDOUT_FILENO);
		if (*fd_std != -1)
			close(*fd_std);
	}
	free_pipeline(pip);
}

static void	handle_exec(char **argv, t_data *data, t_pipeline *pip, int *fd_std)
{
	if (is_hd(pip))
		here_doc_init(pip);
	if (pip->pipe_cnt > 0)
		pip->pid = init_pid(pip);
	// if (is_pipe(argv) && pip->start != pip->pipe_cnt && pip->pipe_cnt > 0)
	// {
	// 	data->exit_code = pipex(pip, data);
	// 	free_pipeline(pip);
	// }
	if (pip->start != pip->pipe_cnt && pip->pipe_cnt > 0)
	{
		data->exit_code = pipex(pip, data);
		free_pipeline(pip);
	}
	else if (is_builtin(pip->cmds[0]))
		fds_dup(fd_std, pip, data);
	else if (argv)
	{
		// free_tab(argv);
		simple_exec(pip, data);
		if (pip)
			free_pipeline(pip);
	}
}

void	execute_command(char **argv, t_data *data)
{
	t_pipeline	*pip;
	int			fd_std;

	fd_std = -1;
	if (!argv || !argv[0])
		return ;
	// if (!check_redir_pipe(argv))
	// {
	// 	free_tab(argv);
	// 	return ;
	// }
	pip = parse_pipeline(argv, data);
	print_pipeline(pip);
	init_pipe_start(pip);
	handle_exec(argv, data, pip, &fd_std);
}

void	send_to_exec(char **argv, t_data *data)
{
	(void)argv;
	int		i;
	int		exit_code;
	bool	exec_next;
	char	**sub_cmd;

	i = 0;
	exit_code = 0;
	exec_next = true;
	sub_cmd = NULL;

	while (data->lexingv && data->lexingv[i])
	{
		int start = i;
		while (data->lexingv[i] && ft_strcmp(data->lexingv[i], "&&") != 0 && ft_strcmp(data->lexingv[i], "||") != 0)
			i++;

		sub_cmd = ft_subarray(data->lexingv, start, i);
		if (!sub_cmd)
			return;

		if (exec_next)
		{
			execute_command(sub_cmd, data);
			exit_code = data->exit_code;
		}

		// Libérer `sub_cmd` après exécution
		// free_tab(sub_cmd);

		// Vérifier les opérateurs logiques && et ||
		if (data->lexingv[i])
		{
			if (ft_strcmp(data->lexingv[i], "&&") == 0)
				exec_next = (exit_code == 0);
			else if (ft_strcmp(data->lexingv[i], "||") == 0)
				exec_next = (exit_code != 0);
			i++;  // Passer au token suivant
		}
		else
			free_tab(sub_cmd);
		
	}
}
