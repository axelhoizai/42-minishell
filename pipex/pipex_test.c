/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:37:52 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/11 00:41:40 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char **cmd, t_pipeline *pip, t_data *data)
{
	char	*cmd_path;

	if (!cmd || !cmd[0])
	{
		write(2, "Invalid command\n", 16);
		exit(127);
	}
	cmd_path = get_path(cmd[0], data->my_envp);
	if (!cmd_path)
	{
		write(2, "command not found: ", 19);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, "\n", 1);
		free_pipeline(pip);
		exit(127);
	}
	execve(cmd_path, cmd, data->my_envp);

	/* Vérification d'échec spécifique à `execve` */
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == -1)
		{
			write(2, "Permission denied: ", 19);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, "\n", 1);
			exit(126);
		}
	}

	write(2, "Execution error: ", 17);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "\n", 1);
	exit(127);
}

void	ft_close_fdin(t_pipeline *pip)
{
	int	i;

	i = 0;
	while (pip->cmds[i])
	{
		if (pip->cmds[i]->fd_in > -1)
			close(pip->cmds[i]->fd_in);
		i++;
	}
}

void	ft_close_fdout(t_pipeline *pip)
{
	int	i;

	i = 0;
	while (pip->cmds[i])
	{
		if (pip->cmds[i]->fd_out > -1)
			close(pip->cmds[i]->fd_out);
		i++;
	}
}

/* Gestion du premier processus de la pipeline */
static void	first_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
{
	pid_t	child;

	if (cmd->fd_in == -1)
		return ;
	if (pipe(p_fd) == -1)
		exit(PIPE_ERROR);
	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		close(p_fd[0]);
		/* Gestion des fichiers d'entrée et sortie */
		if (cmd->fd_in > -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		else if (fd_files[0] > -1)
			dup2(fd_files[0], STDIN_FILENO);
		if (cmd->fd_out > -1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		else
			dup2(p_fd[1], STDOUT_FILENO);
		close_fds(pip);
		close(p_fd[1]);
		if (is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			exit(0);
		}
		execute(cmd->args, pip, data);
	}
	close(p_fd[1]);
}

/* Gestion des processus intermédiaires */
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
		dup2(p_fd[0], STDIN_FILENO);
		dup2(temp_fd[1], STDOUT_FILENO);
		close_fds(pip);
		close(p_fd[0]);
		close(p_fd[1]);
		close(temp_fd[0]);
		close(temp_fd[1]);
		if (is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			exit(0);
		}
		execute(cmd->args, pip, data);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	p_fd[0] = temp_fd[0];
	p_fd[1] = temp_fd[1];
	close(p_fd[1]);
}

/* Gestion du dernier processus de la pipeline */
static int	last_pipe(t_pipeline *pip, int *p_fd, t_data *data, int *fd_files)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		if (fd_files[0] > -1)
			dup2(fd_files[0], STDIN_FILENO);
		else
			dup2(p_fd[0], STDIN_FILENO);
		if (fd_files[1] > -1)
			dup2(fd_files[1], STDOUT_FILENO);
		close_fds(pip);
		close(p_fd[0]);
		close(p_fd[1]);
		if (is_builtin(pip->cmds[pip->cmd_count - 1]->args[0]))
		{
			handle_builtins(pip->cmds[pip->cmd_count - 1], pip, data);
			exit(0);
		}
		execute(pip->cmds[pip->cmd_count - 1]->args, pip, data);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/* Gestion des here_doc */
void	here_doc_checker(int *fd_files, t_pipeline *pip, t_data *data, int *i)
{
	int	p_fd[2];

	if (pip->cmds[*i]->heredoc)
	{
		if (pipe(p_fd) == -1)
			exit(PIPE_ERROR);
		if (fork() == 0)
		{
			close(p_fd[0]);
			here_doc(pip, p_fd, data);
			close(p_fd[1]);
			ms_lstclear(&data->env_ms);
			free_tab(data->my_envp);
			free_pipeline(pip);
			exit(0);
		}
		close(p_fd[1]);
		fd_files[0] = p_fd[0];
		wait(NULL);
	}
	else
		fd_files[0] = pip->cmds[*i]->fd_in;
}

/* Fonction principale qui gère l'exécution des pipes */
int	pipex(t_pipeline *pip, t_data *data)
{
	int		p_fd[2];
	int		fd_files[2];
	int		i;
	int		status;

	i = 0;
	here_doc_checker(fd_files, pip, data, &i);
	first_pipe(pip->cmds[i], pip, p_fd, data, fd_files);
	i++;
	while (i < pip->cmd_count - 1)
	{
		here_doc_checker(fd_files, pip, data, &i);
		multi_pipe(pip->cmds[i], pip, p_fd, data);
		i++;
	}
	here_doc_checker(fd_files, pip, data, &i);
	status = last_pipe(pip, p_fd, data, fd_files);
	i = 0;
	while (i < pip->cmd_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (status);
}
