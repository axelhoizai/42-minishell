/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:04:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 19:24:49 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute(char **cmd, char **envp)
{
	// char	**cmd_args;
	char	*cmd_path;

	if (ft_strstr(cmd[0], "./"))
		script_checker(cmd[0]);
	// cmd_args = utils_parse_args(cmd);
	if (!cmd || !cmd[0])
	{
		// free_tab(cmd_args);
		print_error("Invalid command", NULL, CMD_NOT_FOUND);
		return ;
	}
	cmd_path = get_path(cmd[0], envp);
	if (ft_strstr(cmd[0], "./"))
		cmd_path = cmd[0];
	if (execve(cmd_path, cmd, envp) == -1)
	{
		// free_tab(cmd_args);
		print_error("command not found : ", ft_strtok(cmd[0], " "), CMD_NOT_FOUND);
	}
}

static void	first_pipe(t_command *cmd, int *p_fd, char **envp, int *fd_files)
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
		if (dup2(fd_files[0], STDIN_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		if (dup2(p_fd[1], STDOUT_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		close(fd_files[0]);
		close(p_fd[1]);
		execute(cmd->args, envp);
	}
	close(fd_files[0]);
	close(p_fd[1]);
}

static void	multi_pipe(t_command *cmd, int *p_fd, char **envp)
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
		execute(cmd->args, envp);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	p_fd[0] = temp_fd[0];
	p_fd[1] = temp_fd[1];
}

static int	last_pipe(t_pipeline *pip, int *p_fd, char **envp, int *fd_files)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		open_outfile(pip, pip->cmd_count, fd_files, p_fd);
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		if (dup2(fd_files[1], STDOUT_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		close(p_fd[0]);
		close(p_fd[1]);
		close(fd_files[1]);
		execute(pip->commands[pip->cmd_count - 1]->args, envp);
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
	// t_arg	args;
	int		status;

	if (args_checker(pip) == -1)
		return (1);
	here_doc_checker(fd_files, pip, data);
	i = 0;
	// fd_files[0] = open_file(pip->commands[i]->input_file, 1, p_fd);
	first_pipe(pip->commands[i], p_fd, data->my_envp, fd_files);
	i++;
	while (i < pip->cmd_count - 1)
	{
		multi_pipe(pip->commands[i], p_fd, data->my_envp);
		i++;;
	}
	status = last_pipe(pip, p_fd, data->my_envp, fd_files);
	while (--i > 0)
		waitpid(-1, NULL, 0);
	// free_pipeline(pip);
	return (status);
}
