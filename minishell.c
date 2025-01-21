/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 16:46:46 by mdemare          ###   ########.fr       */
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

char	**get_argv(char *input)
{
	char	**argv;
	int		argc;

	argv = NULL;
	argc = 0;
	if (input)
	{
		argv = ft_split(input, ' ');
		if (argv)
		{
			while (argv[argc])
				argc++;
		}
		if (ft_strcmp(argv[0], "exit") == 0)
			handle_exit(input, argv);
		else if (ft_strcmp(argv[0], "pwd") == 0)
			printf("%s\n", get_dir());
		else if (ft_strcmp(argv[0], "cd") == 0)
			change_dir(argc, argv[1]);
		else if (ft_strcmp(argv[0], "echo") == 0)
			ft_echo(argv);
	}
	return (argv);
}

int	main(int ac, char **envp)
{
	char	*input;
	char	**argv;
	char	*prompt;

	(void)envp;
	(void)ac;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		prompt = get_promt();
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			handle_exit(input, argv);
			break ;
		}
		if (*input)
			add_history(input);
		argv = get_argv(input);
		// if (argv && input)
			free_tab(argv);
		free(input);
	}
	return (0);
}
