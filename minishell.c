/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 11:13:33 by mdemare          ###   ########.fr       */
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

void	handle_builtins(int argc, char **argv, char *input, t_data *data)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv, data);
	else if (ft_strcmp(argv[0], "cd") == 0)
		change_dir(argc, argv[1]);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		get_dir(data);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(data->env_ms, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argc, argv[1]);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(argv[0], "exit") == 0)
		handle_exit(input, argv);
	else if (ft_strcmp(argv[0], "clear") == 0)
		printf("\033[H\033[J");
}

void	ft_init(t_data	*data, char **envp, int is_start)
{
	if (is_start == 0)
	{
		data->exit_code = 0;
		// data->envp = envp;
		init_env_ms(data, envp);
		is_start = 1;	
	}
}

void	sh_tester(char *input, t_data *data)
{
	char	**argv;

	argv = NULL;

	while ((input = get_next_line(STDIN_FILENO)) != NULL)
	{
		// printf("input = %s\n", input);
		if (input)
			argv = get_argv(input, data);
		if (!argv)
		{
			free(input);
			continue ;
		}
		free(input);
	}
	handle_exit(input, argv);
	// free(input);
	// exit (0);
}

char	**get_argv(char *input, t_data *data)
{
	char	**argv;
	int		argc;
	char	*builtins;

	argv = NULL;
	argc = 0;
	if (input)
	{
		builtins = ft_strtok(input, "\n");
		while (builtins != NULL)
		{
			//printf("builtins = %s\n", builtins);
			argv = parse_args(builtins);
			while (argv && argv[argc])
				argc++;
			// print_tab(argv);
			if (argc > 0)
				handle_builtins(argc, argv, builtins, data);
			builtins = ft_strtok(NULL, "\n");
			argc = 0;
			free_tab(argv);
		}
	}
	return (argv);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**argv;
	char	*prompt;
	t_data	data;
	int		is_start;

	is_start = 0;
	(void)ac;
	(void)av;
	argv = NULL;
	ft_init(&data, envp, is_start);
	signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL, &data);
	while (1)
	{
		prompt = get_promt();
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			handle_exit(input, argv);
			break;
		}
		if (*input)
			add_history(input);
		argv = get_argv(input, &data);
		free(input);
		// if (argv)
		// 	free_tab(argv);
	}
	return (0);
}

