/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 13:43:46 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	get_user_and_host()
{
	char *username;
	char hostname[1024];

	username = getenv("USER");
	if (!username)
		username = "unknown";

	if (gethostname(hostname, sizeof(hostname)) != 0)
		strcpy(hostname, "unknown");
	printf("User: %s\n", username);
	printf("Host: %s\n", hostname);
}


int	main(int argc, char **argv, char **envp)
{
	char	*input;
	(void)argc;
	(void)argv;
	(void)envp;
	
	signal(SIGINT, handle_sigint);
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // CTRL+D
		{
			printf("Exiting...\n");
			break;
		}
		if (*input)
			add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}