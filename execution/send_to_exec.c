/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 10:05:10 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_pipe(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '|'))
		{
			free_tab(argv);
			return (true);
		}
		i++;
	}
	// free_tab(argv);
	return (false);
}

bool	is_builtin(t_command *cmd)
{
	if (cmd->args)
	{
		if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "env") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "clear") == 0)
			return (true);
	}
	return (false);
}

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

void	send_to_exec(int argc, char **argv, t_data *data)
{
	t_pipeline	*pip;
	int			fd_std;

	(void)argc;
	fd_std = -1;
	argv = expand_wildcard(argv);
	pip = parse_pipeline(argv, data);
	print_pipeline(pip);
	init_pipe_start(pip);
	if (is_hd(pip))
		here_doc_init(pip);
	if (pip->pipe_cnt > 0)
		pip->pid = init_pid(pip);
	if (is_pipe(argv) && pip->start != pip->pipe_cnt && pip->pipe_cnt > 0)
	{
		data->exit_code = pipex(pip, data);
		free_pipeline(pip);
	}
	else if (is_builtin(pip->cmds[0]))
		fds_dup(&fd_std, pip, data);
	else if (argv)
	{
		simple_exec(pip, data);
		if (pip)
			free_pipeline(pip);
	}
}

//pour || voir leak et norme
// void	execute_command(char **cmd, char **argv, t_data *data)
// {
// 	t_pipeline	*pip;
// 	int			fd_std;

// 	fd_std = -1;
// 	if (!cmd || !cmd[0])
// 		return;
//  cmd = expand_wildcard(cmd);
// 	pip = parse_pipeline(cmd, data);
// 	print_pipeline(pip);
// 	init_pipe_start(pip);
// 	if (is_hd(pip))
// 		here_doc_init(pip);
// 	if (pip->pipe_cnt > 0)
// 		pip->pid = init_pid(pip);
// 	if (is_pipe(cmd) && pip->start != pip->pipe_cnt && pip->pipe_cnt > 0)
// 	{
// 		data->exit_code = pipex(pip, data);
// 		free_pipeline(pip);
// 	}
// 	else if (is_builtin(pip->cmds[0]))
// 		fds_dup(&fd_std, pip, data);
// 	else if (cmd)
// 	{
// 		simple_exec(pip, data);
// 		if (pip)
// 			free_pipeline(pip);
// 	}
// 	else if (argv)
// 	{
// 		simple_exec(pip, data);
// 		if (pip)
// 			free_pipeline(pip);
// 	}
// }

// void	send_to_exec(int argc, char **argv, t_data *data)
// {
// 	char		**cmd1;
// 	char		**cmd2;
// 	int			i;

// 	(void)argc;
// 	cmd1 = argv;
// 	cmd2 = NULL;
// 	i = 0;
// 	while (argv[i])
// 	{
// 		if (ft_strcmp(argv[i], "||") == 0)
// 		{
// 			argv[i] = NULL;
// 			cmd2 = &argv[i + 1];
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (cmd1 && cmd1[0])
// 		execute_command(cmd1, argv, data);
// 	if (cmd2 && cmd2[0] && data->exit_code > 0)
// 	{
// 		if (ft_strcmp(cmd2[0], "echo") == 0)
// 			cmd2[1] = ft_itoa(data->exit_code);
// 		execute_command(cmd2, argv, data);
// 	}
// }
