/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/27 17:22:40 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	pipe_test(int argc, char **argv, char *input)
{
	int	i;

	i = 0;
	(void)argc;
	(void)input;
	// < << > >> |
	while (argv[i])
	{
		if (ft_strtok(argv[i], "<>|"))
			printf("tok argv[i] = %s\n", argv[i]);
		else if (ft_strcmp(argv[i], "<") == 0)
			printf("< found, i = %d\n", i);
		else if (ft_strcmp(argv[i], ">") == 0)
			printf("> found, i = %d\n", i);
		else if (ft_strcmp(argv[i], "<<") == 0)
			printf("<< found, i = %d\n", i);
		else if (ft_strcmp(argv[i], ">>") == 0)
			printf(">> found, i = %d\n", i);
		else if (ft_strcmp(argv[i], "|") == 0)
			printf("| found, i = %d\n", i);
		// printf("argv[i] = %s\n", argv[i]);
		i++;
	}
	ft_strtok(NULL, "<>|");
	// < infile cmd
	// | cmd |
	// cmd
	// > outfile
}

void	handle_builtins(int argc, char **argv, char *input)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		change_dir(argc, argv[1]);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		get_dir();
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argc, argv[1]);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(argv[0], "exit") == 0)
		handle_exit(argv);
	else if (ft_strcmp(argv[0], "clear") == 0)
		printf("\033[H\033[J");
	else if (ft_strchr(input, '|'))
		pipe_test(argc, argv, input);
	else
		exec(argv, input, g_data.envp);
}

void	sh_tester(char *input)
{
	char	**argv;

	argv = NULL;
	while ((input = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (input)
			argv = get_argv(input);
		if (!argv)
		{
			free(input);
			continue ;
		}
		free(input);
	}
	handle_exit_tester(argv);
}

char	**get_argv(const char *input)
{
	char	**argv;
	int		argc;
	char	**builtins;
	int		i;
	char	*tmp;

	i = 0;
	argv = NULL;
	argc = 0;
	if (input)
	{
		tmp = ft_strdup(input);
		tmp = replace_double_ampersand(tmp);
		builtins = ft_split(tmp, '\n');
		while (builtins[i])
		{
			argv = parse_args(builtins[i]);
			while (argv && argv[argc])
				argc++;
			if (argc > 0)
				handle_builtins(argc, argv, builtins[i]);
			argc = 0;
			free_tab(argv);
			i++;
			if (g_data.exit_code > 0)
				break ;
		}
		if (tmp)
			free(tmp);
		free_tab(builtins);
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**argv;
	char	*prompt;
	int		is_start;
	char	exit_code;

	is_start = 0;
	(void)ac;
	(void)av;
	argv = NULL;
	ft_init(envp, is_start);
	signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL);
	while (1)
	{
		prompt = get_promt();
		input = readline(prompt);
		exit_code = g_data.exit_code;
		free(prompt);
		if (!input)
		{
			free(input);
			handle_exit(argv);
			break ;
		}
		if (*input)
			add_history(input);
		argv = get_argv(input);
		free(input);
	}
	return (exit_code);
}
