// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex_preview.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/11 21:01:06 by kalicem           #+#    #+#             */
// /*   Updated: 2025/02/11 21:01:08 by kalicem          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// void	execute(char **cmd, t_pipeline *pip, t_data *data)
// {
// 	char	*cmd_path;

// 	if (ft_strstr(cmd[0], "./"))
// 		script_checker(cmd[0]);
// 	if (!cmd || !cmd[0])
// 	{
// 		print_error("Invalid command", NULL, CMD_NOT_FOUND);
// 		return ;
// 	}
// 	cmd_path = get_path(cmd[0], data->my_envp);
// 	if (ft_strstr(cmd[0], "./"))
// 	{
// 		free(cmd_path);
// 		cmd_path = cmd[0];
// 	}
// 	if (execve(cmd_path, cmd, data->my_envp) == -1)
// 	{
// 		free_tab(data->my_envp);
// 		ms_lstclear(&data->env_ms);
// 		print_error("command not found : ", ft_strtok(cmd[0], " "), CMD_NOT_FOUND);
// 		free_pipeline(pip);
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
// 		if (cmd->fd_in == -1)
// 			fd_files[0] = open("/dev/null", O_RDONLY);
// 		dup2(fd_files[0], STDIN_FILENO);
// 		if (cmd->fd_out > -1)
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
// 		ft_close_fdin(pip);
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
// 	// if (fd_files[0] > -1)
// 	// 	close(fd_files[0]);
// 	close(p_fd[1]);
// }

// static void	multi_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
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
// 		if (dup2(p_fd[0], STDIN_FILENO) == -1)
// 			exit(DUPLICATE_ERROR);
// 		if (dup2(temp_fd[1], STDOUT_FILENO) == -1)
// 			exit(DUPLICATE_ERROR);
// 		close(p_fd[0]);
// 		close(p_fd[1]);
// 		close(temp_fd[0]);
// 		close(temp_fd[1]);
// 		ft_close_fdin(pip);
// 		ft_close_fdout(pip);
// 		if (is_builtin(cmd->args[0]))
// 		{
// 			handle_builtins(cmd, pip, data);
// 			exit (0);
// 		}
// 		else
// 			execute(cmd->args, pip, data);
// 	}
// 	p_fd[0] = temp_fd[0];
// 	p_fd[1] = temp_fd[1];
// 	close(p_fd[1]);
// 	// close(p_fd[0]);
// }

// static int	last_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
// {
// 	pid_t	child;
// 	int		status;

// 	child = fork();
// 	if (child == -1)
// 		exit(FORK_ERROR);
// 	if (child == 0)
// 	{
// 		fd_files[1] = pip->cmds[pip->cmd_count - 1]->fd_out;
// 		if (fd_files[0] > -1)
// 			dup2(pip->cmds[pip->cmd_count - 1]->fd_in, STDIN_FILENO);
// 		else if (pip->cmds[pip->cmd_count - 1]->fd_in == -1)
// 		{
// 			pip->cmds[pip->cmd_count - 1]->fd_in = open("/dev/null", O_RDONLY);
// 			dup2(pip->cmds[pip->cmd_count - 1]->fd_in, STDIN_FILENO);
// 		}
// 		else
// 			dup2(p_fd[0], STDIN_FILENO);
// 		if (fd_files[1] == -2)
// 			fd_files[1] = 1;
// 		else if (fd_files[1] == -1)
// 			fd_files[1] = open("/dev/null", O_RDONLY);
// 		if (dup2(fd_files[1], STDOUT_FILENO) == -1)
// 				exit(DUPLICATE_ERROR);
// 		close(p_fd[0]);
// 		close(p_fd[1]);
// 		ft_close_fdin(pip);
// 		ft_close_fdout(pip);
// 		if (is_builtin(pip->cmds[pip->cmd_count - 1]->args[0]))
// 		{
// 			handle_builtins(pip->cmds[pip->cmd_count - 1], pip, data);
// 			exit (0);
// 		}
// 		else
// 		{
// 			execute(pip->cmds[pip->cmd_count - 1]->args, pip, data);
// 		}
// 	}
// 	close(p_fd[0]);
// 	close(p_fd[1]);
// 	// if (pip->cmds[1]->fd_out > -1)
// 	// 	close(pip->cmds[1]->fd_out);
// 	waitpid(child, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }

// int	pipex(t_pipeline *pip, t_data *data)
// {
// 	int		p_fd[2];
// 	int		fd_files[2];
// 	int		i;
// 	int		status;

// 	// if (args_checker(pip) == -1)
// 	// 	return (1);
// 	i = 0;
// 	here_doc_checker(fd_files, pip, data, &i);
// 	first_pipe(pip->cmds[i], pip, p_fd, data, fd_files);
// 	i++;
// 	while (i < pip->cmd_count - 1)
// 	{
// 		here_doc_checker(fd_files, pip, data, &i);
// 		multi_pipe(pip->cmds[i], pip, p_fd, data);
// 		i++;
// 	}
// 	here_doc_checker(fd_files, pip, data, &i);
// 	status = last_pipe(pip, p_fd, data, fd_files);
// 	i = 0;
// 	while (i < pip->cmd_count)
// 	{
// 		waitpid(-1, NULL, 0);
// 		i++;
// 	}
// 	return (status);
// }