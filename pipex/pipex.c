// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/02 14:04:52 by mdemare           #+#    #+#             */
// /*   Updated: 2025/02/11 09:41:23 by mdemare          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// void	execute(char **cmd, t_pipeline *pip, t_data *data)
// {
// 	char	*cmd_path;

// 	if (!cmd || !cmd[0])
// 	{
// 		print_error("Invalid command", NULL, CMD_NOT_FOUND);
// 		exit(CMD_NOT_FOUND);
// 	}
// 	cmd_path = get_path(cmd[0], data->my_envp);
// 	if (!cmd_path)
// 	{
// 		print_error("command not found : ", cmd[0], CMD_NOT_FOUND);
// 		free_pipeline(pip);
// 		exit(CMD_NOT_FOUND);
// 	}
// 	// if (ft_strstr(cmd[0], "./"))
// 	// {
// 	// 	free(cmd_path);
// 	// 	cmd_path = cmd[0];
// 	// }
// 	if (execve(cmd_path, cmd, data->my_envp) == -1)
// 	{
// 		if (access(cmd_path, F_OK) == 0)
// 		{
// 			if (access(cmd_path, X_OK) == -1)
// 			{
// 				print_error("Permission denied: ", cmd[0], PERMISSION_DENIED);
// 				exit(PERMISSION_DENIED);
// 			}
// 		}
// 		print_error("Execution error: ", cmd[0], CMD_NOT_FOUND);
// 		exit(CMD_NOT_FOUND);
// 	}

// }

// void	ft_close_fdin(t_pipeline *pip)
// {
// 	int	i;

// 	i = 0;
// 	while (pip->cmds[i])
// 	{
// 		if (pip->cmds[i]->fd_in > -1)
// 			close(pip->cmds[i]->fd_in);
// 		i++;
// 	}
// }

// void	ft_close_fdout(t_pipeline *pip)
// {
// 	int	i;

// 	i = 0;
// 	while (pip->cmds[i])
// 	{
// 		if (pip->cmds[i]->fd_out > -1)
// 			close(pip->cmds[i]->fd_out);
// 		i++;
// 	}
// }

// static void	first_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
// {
// 	pid_t	child;

// 	if (cmd->fd_in == -1)
// 		return ;
// 	if (pipe(p_fd) == -1)
// 		exit(PIPE_ERROR);
// 	child = fork();
// 	if (child == -1)
// 		exit(FORK_ERROR);
// 	if (child == 0)
// 	{
// 		close(p_fd[0]);
// 		if (fd_files[0] != -1)
// 		{
// 			dup2(fd_files[0], STDIN_FILENO);
// 			close(fd_files[0]);
// 		}
// 		if (cmd->fd_out > -1 && pip->pipe_cnt > 0)
// 			dup2(cmd->fd_out, STDOUT_FILENO);
// 		else
// 		{
// 			if (cmd->fd_in > -1 && cmd->fd_out == -2)
// 				dup2(p_fd[1], STDOUT_FILENO);
// 			else if (cmd->fd_in == -1)
// 			{
// 				fd_files[1] = open("/dev/null", O_RDONLY);
// 				dup2(fd_files[1], STDOUT_FILENO);
// 				close(fd_files[1]);
// 			}
// 		}
// 		if (cmd->fd_in == -1)
// 			close(fd_files[0]);
// 		// ft_close_fdin(pip);
	
// 		ft_close_fdout(pip);
// 		close(p_fd[1]);
// 		if (is_builtin(cmd->args[0]))
// 		{
// 			handle_builtins(cmd, pip, data);
// 			exit (0);
// 		}
// 		else
// 			execute(cmd->args, pip, data);
// 	}
// 	close(p_fd[1]);
// }

// void	multi_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
// {
// 	pid_t	child;
// 	int		temp_fd[2];

// 	if (pipe(temp_fd) == -1)
// 		exit(PIPE_ERROR);
// 	child = fork();
// 	if (child == -1)
// 		exit(FORK_ERROR);
// 	if (child == 0)
// 	{
// 		dup2(p_fd[0], STDIN_FILENO);
// 		close(p_fd[0]);
// 		dup2(temp_fd[1], STDOUT_FILENO);
// 		close(temp_fd[1]);
// 		close(temp_fd[0]);
// 		if (is_builtin(cmd->args[0]))
// 		{
// 			handle_builtins(cmd, pip, data);
// 			exit(0);
// 		}
// 		execute(cmd->args, pip, data);
// 	}
// 	close(p_fd[0]);
// 	close(p_fd[1]);
// 	p_fd[0] = temp_fd[0];
// 	p_fd[1] = temp_fd[1];
// 	close(p_fd[1]);
// }

// int	last_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
// {
// 	pid_t	child;
// 	int		status;

// 	child = fork();
// 	if (child == -1)
// 		exit(FORK_ERROR);
// 	if (child == 0)
// 	{
// 		if (fd_files[0] > -1 || isatty(STDIN_FILENO) == 0)
// 		{
// 			dup2(fd_files[0], STDIN_FILENO);
// 			close(fd_files[0]);
// 		}
// 		else if (isatty(STDIN_FILENO) == 0)
// 			dup2(p_fd[0], STDIN_FILENO);

// 		if (fd_files[1] > -1)
// 		{
// 			dup2(fd_files[1], STDOUT_FILENO);
// 			close(fd_files[1]);
// 		}
// 		close(p_fd[0]);
// 		close(p_fd[1]);
// 		ft_close_fdin(pip);
// 		ft_close_fdout(pip);
// 		if (is_builtin(pip->cmds[pip->cmd_count - 1]->args[0]))
// 		{
// 			handle_builtins(pip->cmds[pip->cmd_count - 1], pip, data);
// 			exit(0);
// 		}
// 		execute(pip->cmds[pip->cmd_count - 1]->args, pip, data);
// 	}
// 	close(p_fd[0]);
// 	close(p_fd[1]);

// 	waitpid(child, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }

// int	pipex(t_pipeline *pip, t_data *data)
// {
// 	int	p_fd[2];
// 	int	fd_files[2];
// 	int	i = 0;
// 	int	status;

// 	fd_files[0] = -1;
// 	fd_files[1] = -1;
// 	here_doc_checker(fd_files, pip, data, &i);
// 	// if (pip->cmds[i]->fd_in > 0)
// 	// 	fd_files[0] = pip->cmds[0]->fd_in;
// 	first_pipe(pip->cmds[i], pip, p_fd, data, fd_files);
// 	i++;
// 	while (i < pip->cmd_count - 1)
// 	{
// 		here_doc_checker(fd_files, pip, data, &i);
// 		multi_pipe(pip->cmds[i], pip, p_fd, data);
// 		i++;
// 	}
// 	status = last_pipe(pip, p_fd, data, fd_files);
// 	if (fd_files[0] > 0) 
// 		close(fd_files[0]);
// 	if (fd_files[1] > 0)
// 		close(fd_files[1]);
// 	i = 0;
// 	while (i < pip->cmd_count)
// 	{
// 		waitpid(-1, NULL, 0);
// 		i++;
// 	}
// 	return status;
// }
