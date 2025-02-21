/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 14:13:14 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_execute(t_pipeline *pip, t_data *data, char *cmd_path)
{
	(void)cmd_path;
	ms_lstclear(&data->env_ms);
	free_tab(data->my_envp);
	free_term(data);
	free_pipeline(pip);
	free(cmd_path);
	free(data->pwd);
	free(data->oldpwd);
}

static char	*execute_checker(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (!cmd || !cmd[0])
	{
		ft_print_error(NULL, NULL, "Invalid command");
		// free_term(data); //probleme de term??
		exit(127);
	}
	cmd_path = get_path(cmd[0], data->my_envp);
	if (!cmd_path)
	{
		ft_print_error(NULL, cmd[0], "command not found");
		free_execute(pip, data, cmd_path);
		exit(127);
	}
	if (ft_strstr(cmd[0], "./"))
	{
		free(cmd_path);
		cmd_path = cmd[0];
	}
	return (cmd_path);
}

// void	execute(char **cmd, t_pipeline *pip, t_data *data)
// {
// 	char	*cmd_path;

// 	cmd_path = NULL;
// 	if (ft_str_startwith(cmd[0], "./") && ft_str_endwith(cmd[0], "sh"))
// 	{
// 		cmd = script_checker(cmd);
// 		if (!cmd_path)
// 			cmd_path = cmd[0];
// 	}
// 	else if (ft_str_startwith(cmd[0], "../") || ft_str_countchar(cmd[0], '.') > 2)
// 	{
// 		if (ft_str_countchar(cmd[0], '.') == 2)
// 			ft_print_error(NULL, ft_strtok(cmd[0], " "), "Is a directory");
// 		else
// 			ft_print_error(NULL, ft_strtok(cmd[0], " "), "No such file or directory");
// 		free_execute(pip, data, cmd_path);
// 		exit(127);
// 	}
// 	else if ((ft_str_startwith(cmd[0], "./") && !ft_str_endwith(cmd[0], ".sh"))
// 			|| (cmd[0][0] == '/' && access(cmd[0], R_OK) == -1))
// 	{
// 		ft_print_error(NULL, ft_strtok(cmd[0], " "), "No such file or directory");
// 		free_execute(pip, data, cmd_path);
// 		exit(127);
// 	}
// 	else 
// 		cmd_path = execute_checker(cmd, pip, data);
// 	print_tab(cmd);
// 	execve(cmd_path, cmd, data->my_envp);
// 	if (access(cmd_path, F_OK) == 0)
// 	{
// 		if (access(cmd_path, X_OK) == -1)
// 		{
// 			ft_print_error(NULL, cmd[0], "Permission denied");
// 			free_execute(pip, data, cmd_path);
// 			exit(126);
// 		}
// 	}
// 	ft_print_error(NULL, cmd[0], "Execution error");
// 	free_execute(pip, data, cmd_path);
// 	exit(127);
// }

static char	*check_command_path(char **cmd, t_pipeline *pip, t_data *data, char *cmd_path)
{
	(void)pip;
	(void)data;
	
	if (ft_str_startwith(cmd[0], "./") && ft_str_endwith(cmd[0], "sh"))
	{
		cmd = script_checker(cmd);
		if (!cmd_path)
			cmd_path = cmd[0];
	}
	else if (ft_str_startwith(cmd[0], "../") || ft_str_countchar(cmd[0], '.') > 2)
	{
		// int fd = -1;
		if(access(cmd[0], F_OK) == -1)
			ft_print_error(NULL, ft_strtok(cmd[0], " "), "No such file or directory");
		else if (ft_str_countchar(cmd[0], '.') == 2)
			ft_print_error(NULL, ft_strtok(cmd[0], " "), "Is a directory");
		else
			ft_print_error(NULL, ft_strtok(cmd[0], " "), "No such file or directory");
		data->exit_code = 127;

		free_execute(pip, data, cmd_path);
		exit(127);
	}
	else if ((ft_str_startwith(cmd[0], "./") && !ft_str_endwith(cmd[0], ".sh"))
			|| (cmd[0][0] == '/' && access(cmd[0], R_OK) == -1))
	{
		ft_print_error(NULL, ft_strtok(cmd[0], " "), "No such file or directory");
		data->exit_code = 127;
		free_execute(pip, data, cmd_path);
		exit(127);
	}
	return (cmd_path);
}

void	execute(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = check_command_path(cmd, pip, data, cmd_path);
	if (!cmd_path)
		cmd_path = execute_checker(cmd, pip, data);
	execve(cmd_path, cmd, data->my_envp);
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == -1)
		{
			ft_print_error(NULL, cmd[0], "Permission denied");
			data->exit_code = 126;
			free_execute(pip, data, cmd_path);
			exit(126);
		}
	}
	ft_print_error(NULL, cmd[0], "Execution error");
	data->exit_code = 127;
	free_execute(pip, data, cmd_path);
	exit(127);
}

static void	exec_child(t_pipeline *pip, t_data *data, pid_t	pid)
{
	// int	tty_fd;
	// tty_fd = -1;
	if (pid == 0)
	{
		if (pip->cmds[pip->start]->fd_in > -1)
		{
			dup2(pip->cmds[pip->start]->fd_in, STDIN_FILENO);
			close(pip->cmds[pip->start]->fd_in);
		}
		if (pip->cmds[pip->start]->fd_out > -1)
		{
			dup2(pip->cmds[pip->start]->fd_out, STDOUT_FILENO);
			close(pip->cmds[pip->start]->fd_out);
		}
		// if (!isatty(STDIN_FILENO)) // pour nano, vi, ...
		// {
		// 	tty_fd = open("/dev/tty", O_RDWR);
		// 	if (tty_fd > -1)
		// 	{
		// 		dup2(tty_fd, STDIN_FILENO);
		// 		close(tty_fd);
		// 	}
		// }
		execute(pip->cmds[pip->start]->args, pip, data);
	}
	if (pip->cmds[pip->start]->fd_in > -1)
		close(pip->cmds[pip->start]->fd_in);
	if (pip->cmds[pip->start]->fd_out > -1)
		close(pip->cmds[pip->start]->fd_out);
	// if (tty_fd > -1)
	// 	close(tty_fd);
}

void	simple_exec(t_pipeline *pip, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (pip->cmds[pip->start]->fd_out == -1 || pip->cmds[pip->start]->fd_in == -1)
	{
		if (pip->cmds[pip->start]->fd_in > -1)
			close (pip->cmds[pip->start]->fd_in);
		data->exit_code = 1;
		return ;
	}
	if (pip->cmds[pip->start]->args)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		exec_child(pip, data, pid);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) >= 0)
		{
			if (data->exit_code < 128)
				data->exit_code = WEXITSTATUS(status);
		}
	}
}
