/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:04:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 17:42:15 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	if (ft_strstr(cmd, "./"))
		script_checker(cmd);
	cmd_args = utils_parse_args(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		free_tab(cmd_args);
		print_error("Invalid command", NULL, CMD_NOT_FOUND);
		return ;
	}
	cmd_path = get_path(cmd_args[0], envp);
	if (ft_strstr(cmd_args[0], "./"))
		cmd_path = cmd_args[0];
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free_tab(cmd_args);
		print_error("command not found : ", ft_strtok(cmd, " "), CMD_NOT_FOUND);
	}
}

static void	first_pipe(char *cmd, int *p_fd, char **envp, int *fd_files)
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
		execute(cmd, envp);
	}
	close(fd_files[0]);
	close(p_fd[1]);
}

static void	multi_pipe(char *cmd, int *p_fd, char **envp)
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
		execute(cmd, envp);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	p_fd[0] = temp_fd[0];
	p_fd[1] = temp_fd[1];
}

static int	last_pipe(t_arg args, int *p_fd, char **envp, int *fd_files)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
		exit(FORK_ERROR);
	if (child == 0)
	{
		open_outfile(args.argv, args.argc, fd_files, p_fd);
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		if (dup2(fd_files[1], STDOUT_FILENO) == -1)
			exit(DUPLICATE_ERROR);
		close(p_fd[0]);
		close(p_fd[1]);
		close(fd_files[1]);
		execute(args.argv[args.argc - 2], envp);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	pipex(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	int		fd_files[2];
	int		i;
	t_arg	args;
	int		status;

	if (args_checker(argc, argv) == -1)
		return (1);
	here_doc_checker(fd_files, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		i = 3;
	else
		i = 2;
	first_pipe(argv[i], p_fd, envp, fd_files);
	i++;
	while (i < argc - 2)
		multi_pipe(argv[i++], p_fd, envp);
	args.argv = argv;
	args.argc = argc;
	status = last_pipe(args, p_fd, envp, fd_files);
	while (--i > 0)
		waitpid(-1, NULL, 0);
	return (status);
}
