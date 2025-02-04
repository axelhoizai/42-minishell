/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:04:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 12:36:00 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (ft_strstr(cmd[0], "./"))
		script_checker(cmd[0]);
	if (!cmd || !cmd[0])
	{
		print_error("Invalid command", NULL, CMD_NOT_FOUND);
		return ;
	}
	cmd_path = get_path(cmd[0], data->my_envp);
	if (ft_strstr(cmd[0], "./"))
	{
		free(cmd_path);
		cmd_path = cmd[0];
	}
	if (execve(cmd_path, cmd, data->my_envp) == -1)
	{
		free_tab(data->my_envp);
		ms_lstclear(&data->env_ms);
		print_error("command not found : ", ft_strtok(cmd[0], " "), CMD_NOT_FOUND);
		free_pipeline(pip);
		exit(CMD_NOT_FOUND);
	}
}

static void	first_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
{
	pid_t	child;

	if (pipe(p_fd) == -1)
		exit(PIPE_ERROR);
	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		close(p_fd[0]);
		if (fd_files[0] > -1)
		{
			if (dup2(fd_files[0], STDIN_FILENO) == -1)
				exit(DUPLICATE_ERROR);
		}
		if (dup2(p_fd[1], STDOUT_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		if (fd_files[0] > -1)
			close(fd_files[0]);
		close(p_fd[1]);
		if (is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			exit (0);
		}
		else
			execute(cmd->args, pip, data);
	}
	if (fd_files[0] > -1)
		close(fd_files[0]);
	close(p_fd[1]);
}

static void	multi_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
{
	pid_t	child;
	int		temp_fd[2];

	if (pipe(temp_fd) == -1)
		exit(PIPE_ERROR);
	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		if (dup2(temp_fd[1], STDOUT_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		close(p_fd[0]);
		close(p_fd[1]);
		close(temp_fd[0]);
		close(temp_fd[1]);
		if (is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			exit (0);
		}
		else
			execute(cmd->args, pip, data);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	p_fd[0] = temp_fd[0];
	p_fd[1] = temp_fd[1];
}

static int	last_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		if (pip->cmds[pip->cmd_count - 1]->output_file)
		{
			open_outfile(pip, data, pip->cmd_count, fd_files, p_fd);
			if (dup2(fd_files[1], STDOUT_FILENO) == -1)
				exit(DUPLICATE_ERROR);
		}
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		close(p_fd[0]);
		close(p_fd[1]);
		if (pip->cmds[pip->cmd_count - 1]->output_file && fd_files[1] > -1)
			close(fd_files[1]);
		if (is_builtin(pip->cmds[pip->cmd_count - 1]->args[0]))
		{
			handle_builtins(pip->cmds[pip->cmd_count - 1], pip, data);
			exit (0);
		}
		else
			execute(pip->cmds[pip->cmd_count - 1]->args, pip, data);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	pipex(t_pipeline *pip, t_data *data)
{
	int		p_fd[2];
	int		fd_files[2];
	int		i;
	int		status;

	if (args_checker(pip) == -1)
		return (1);
	here_doc_checker(fd_files, pip, data);
	i = 0;
	first_pipe(pip->cmds[i], pip, p_fd, data, fd_files);
	i++;
	while (i < pip->cmd_count - 1)
	{
		multi_pipe(pip->cmds[i], pip, p_fd, data);
		i++;
	}
	status = last_pipe(pip, p_fd, data, fd_files);
	i = 0;
	while (i < pip->cmd_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (status);
}
