/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 22:11:52 by kalicem          ###   ########.fr       */
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

	if (input)
	{
		printf("You entered: %s\n", input);
		argv = ft_split(input, ' ');
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
		input = readline("$ ");
		if (!input)
		{
			printf("Exiting...\n");
			rl_clear_history();
			free(input);
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
