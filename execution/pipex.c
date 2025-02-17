/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:37:52 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/17 12:55:33 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
static void	first_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
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
		if (cmd->in_error == 1 || cmd->out_error == 1)
		{
			ms_lstclear(&data->env_ms);
			free_tab(data->my_envp);
			free_pipeline(pip);
			close(p_fd[1]);
			exit(1);
		}
		else
		{
			printf("cmd->fd_in : %d\n", cmd->fd_in);
			if (cmd->fd_in > -1)
				dup2(cmd->fd_in, STDIN_FILENO);
			if (cmd->fd_out > -1)
				dup2(cmd->fd_out, STDOUT_FILENO);
			else if (cmd->in_error == 0)
				dup2(p_fd[1], STDOUT_FILENO);
			close(p_fd[1]);
			ft_close_fdin(pip);
			ft_close_fdout(pip);
			if (is_builtin(cmd->args[0]))
			{
				handle_builtins(cmd, pip, data);
				ms_lstclear(&data->env_ms);
				free_tab(data->my_envp);
				free_pipeline(pip);
				exit(0);
			}
			execute(cmd->args, pip, data);
		}
	}
	close(p_fd[1]);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_in == -2)
		cmd->fd_in = p_fd[0];
	if (pip->cmds[1]->fd_in == -2)
		pip->cmds[1]->fd_in = p_fd[0];
	else
		close(p_fd[0]);
}

/* Gestion des processus intermédiaires */
static void	multi_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data, int *i)
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
		if (cmd->in_error == 1 || cmd->out_error == 1)
		{
			ms_lstclear(&data->env_ms);
			free_tab(data->my_envp);
			free_pipeline(pip);
			close(p_fd[1]);
			exit(1);
		}
		if (cmd->fd_in > -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out > -1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		else if (cmd->fd_out < 0 && cmd->out_error == 0 && cmd->in_error == 0)
			dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		ft_close_fdin(pip);
		ft_close_fdout(pip);
		if (is_builtin(cmd->args[0]))
		{
			handle_builtins(cmd, pip, data);
			exit(0);
		}
		execute(cmd->args, pip, data);
	}
	close(p_fd[1]);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_in == -2)
		cmd->fd_in = p_fd[0];
	if (pip->cmds[*i + 1]->fd_in == -2)
		pip->cmds[*i + 1]->fd_in = p_fd[0];
	else
		close(p_fd[0]);
}

/* Gestion du dernier processus de la pipeline */
static int	last_pipe(t_command *cmd, t_pipeline *pip, int *p_fd, t_data *data)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		close(p_fd[1]);
		if (cmd->in_error == 1 || cmd->out_error == 1)
		{
			ms_lstclear(&data->env_ms);
			free_tab(data->my_envp);
			free_pipeline(pip);
			close(p_fd[0]);
			exit(1);
		}
		else
		{
			if (cmd->fd_in > -1)
				dup2(cmd->fd_in, STDIN_FILENO);
			else if (pip->cmds[pip->cmd_count - 2]->fd_out < 0)
				dup2(p_fd[0], STDIN_FILENO);
			if (cmd->fd_out > -1)
				dup2(cmd->fd_out, STDOUT_FILENO);
			close(p_fd[0]);
			close(p_fd[1]);
			ft_close_fdin(pip);
			ft_close_fdout(pip);
			if (is_builtin(pip->cmds[pip->cmd_count - 1]->args[0]))
			{
				handle_builtins(pip->cmds[pip->cmd_count - 1], pip, data);
				ms_lstclear(&data->env_ms);
				free_tab(data->my_envp);
				free_pipeline(pip);
				exit(0);
			}
			execute(pip->cmds[pip->cmd_count - 1]->args, pip, data);
		}
	}
	close(p_fd[0]);
	close(p_fd[1]);
	ft_close_fdin(pip);
	ft_close_fdout(pip);
	// waitpid(child, NULL, 0);
	// waitpid(child, &status, 0);
	// if (WIFEXITED(status) && data->exit_code < 128)
	// 	return (WEXITSTATUS(status));
	return (data->exit_code);
}

/* Fonction principale qui gère l'exécution des pipes */
int	pipex(t_pipeline *pip, t_data *data)
{
	int		p_fd[2];
	int		i;
	int		status;

	i = 0;
	signal(SIGPIPE, SIG_IGN);
	here_doc(pip->cmds[i]);
	first_pipe(pip->cmds[0], pip, p_fd, data);
	i++;
	while (i < pip->cmd_count - 1)
	{
		// here_doc_chck(fd_files, pip, data, &i);
		multi_pipe(pip->cmds[i], pip, p_fd, data, &i);
		i++;
	}
	// here_doc_chck(fd_files, pip, data, &i);
	status = last_pipe(pip->cmds[i], pip, p_fd, data);
	while (i >= 0)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
	return (status);
}
