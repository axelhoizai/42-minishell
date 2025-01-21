/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 13:23:31 by ahoizai          ###   ########.fr       */
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
	get_promt();
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
		// printf("%% %s\n", input);
		argv = ft_split(input, ' ');
		if (argv)
		{
			while (argv[argc])
				argc++;
		}
		if (ft_strcmp(argv[0], "pwd") == 0)
			printf("%s\n", get_dir());
		else if (ft_strcmp(argv[0], "exit") == 0)
			handle_exit(input);
		else if (ft_strcmp(argv[0], "cd") == 0 && argc == 2)
			change_dir(argv[1]);
		else if (ft_strcmp(argv[0], "echo") == 0)
			ft_echo(argv);
		// ft_echo(argv);
	}
	return (argv);
}

int	main(int ac, char **envp)
{
	char	*input;
	char	**argv;

	(void)envp;
	(void)ac;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		get_promt();
		// change_dir("/home/mdemare/");
		// printf("pwd = %s\n", get_dir());
		input = readline("$ ");
		if (!input)
		{
			handle_exit(input);
			break ;
		}
		if (*input)
			add_history(input);
		argv = get_argv(input);
		free(input);
		free_tab(argv);
	}
	return (0);
}
