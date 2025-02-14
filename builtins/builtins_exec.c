/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/14 18:18:08 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	execute(char *cmd, t_data *data)
// {
// 	char	**cmd_args;
// 	char	*cmd_path;

// 	if (ft_strstr(cmd, "./"))
// 		script_checker(cmd);
// 	cmd_args = ft_split(cmd, ' ');
// 	if (!cmd_args || !cmd_args[0])
// 	{
// 		free_tab(cmd_args);
// 		print_error("minishell: Invalid command", NULL, CMD_NOT_FOUND);
// 		return ;
// 	}
// 	cmd_path = get_path(cmd_args[0], data->my_envp);
// 	if (ft_strstr(cmd_args[0], "./"))
// 		cmd_path = cmd_args[0];
// 	if (execve(cmd_path, cmd_args, data->my_envp) == -1)
// 	{
// 		free_tab(data->my_envp);
// 		ms_lstclear(&data->env_ms);
// 		free_tab(cmd_args);
// 		ft_print_error(ft_strtok(cmd, " "), NULL, "command not found");
// 		free(cmd);
// 		data->exit_code = CMD_NOT_FOUND;
// 		exit(CMD_NOT_FOUND);
// 	}
// }

// static char	*parse_cmd(char **argv, char *cmd)
// {
// 	char	*tmp;

// 	if (argv && argv[0] && ft_strcmp(argv[0], "<") == 0)
// 	{
// 		tmp = ft_strjoin(argv[2], " ");
// 		free (cmd);
// 		cmd = ft_strjoin(tmp, argv[1]);
// 		free(tmp);
// 		return (cmd);
// 	}
// 	return (ft_strdup(cmd));
// }

void	exec(t_pipeline *pip, t_data *data)
{
	int		status;
	pid_t	pid[2];
	// int 	fd_files[2];

	// fd_files[0] = -2;
	status = 0;
	if (pip->cmds[0]->fd_out == -1 || pip->cmds[0]->fd_in == -1)
	{
		if (pip->cmds[0]->fd_in > -1)
			close (pip->cmds[0]->fd_in);
		data->exit_code = 1;
		return ;
	}
	if (pip->cmds[0]->args)
	{
		pid[0] = fork();
		if (pid[0] == -1)
			exit(1);
		if (pid[0] == 0)
		{
			if (pip->cmds[0]->fd_in > -1)
			{
				// fd_files[0] = open_file(data, pip->cmds[0]->input_file, 1, NULL);
				dup2(pip->cmds[0]->fd_in, STDIN_FILENO);
				close(pip->cmds[0]->fd_in);
			}
			if (pip->cmds[0]->fd_out > -1)
			{
				// open_outfile(pip, data, pip->cmd_count, fd_files, NULL);
				dup2(pip->cmds[0]->fd_out, STDOUT_FILENO);
				close(pip->cmds[0]->fd_out);
			}
			execute(pip->cmds[0]->args, pip, data);
		}
		if (pip->cmds[0]->fd_in > -1)
			close(pip->cmds[0]->fd_in);
		if (pip->cmds[0]->fd_out > -1)
			close(pip->cmds[0]->fd_out);
		waitpid(pid[0], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) >= 0)
		{
			if (data->exit_code < 128)
				data->exit_code = WEXITSTATUS(status);
		}
	}
}

// void	exec(t_pipeline *pip, t_data *data)
// {
// 	int		status;
// 	pid_t	pid[2];
// 	int 	fd_files[2];

// 	if (pip->cmds[0]->args)
// 	{
// 		pid[0] = fork();
// 		if (pid[0] == -1)
// 			exit(1);
// 		if (pid[0] == 0)
// 		{
// 			if (pip->cmds[0]->input_file)
// 			{
// 				fd_files[0] = open_file(data, pip->cmds[0]->input_file, 1, NULL);
// 				dup2(fd_files[0], STDIN_FILENO);
// 				close(fd_files[0]);
// 			}
// 			if (pip->cmds[0]->output_file)
// 			{
// 				open_outfile(pip, data, pip->cmd_count, fd_files, NULL);
// 				dup2(fd_files[1], STDOUT_FILENO);
// 				close(fd_files[1]);
// 			}
// 			if (is_builtin(pip->cmds[0]->args[0]))
// 			{
// 				handle_builtins(pip->cmds[0], pip, data);
// 				exit (data->exit_code);
// 			}
// 			else
// 				execute(pip->cmds[0]->args, pip, data);
// 		}
// 		waitpid(pid[0], &status, 0);
// 		if (WIFEXITED(status) && WEXITSTATUS(status) >= 0)
// 			data->exit_code = WEXITSTATUS(status);
// 		if (ft_strcmp(pip->cmds[0]->args[0], "exit") == 0)
// 			exit (data->exit_code);
// 	}
// }