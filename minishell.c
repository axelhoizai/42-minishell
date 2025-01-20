/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 16:29:23 by mdemare          ###   ########.fr       */
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

char	*get_promt()
{
	char	*username;
	char	hostname[1024];
	char	*prompt =NULL;
	char	*tmp;
	char	*tmp2;

	username = getenv("USER");
	if (!username)
		username = "unknown";
	if (gethostname(hostname, sizeof(hostname)) != 0)
		ft_strlcpy(hostname, "unknown", ft_strlen("unknown"));
	username = ft_strjoin(username, "@");
	tmp = ft_strtok(hostname, ".");
	tmp2 = ft_strjoin(username, tmp);
	prompt = ft_strdup(tmp2);
	free(username);
	free(tmp2);
	ft_strtok(NULL, ".");
	return (prompt);
}


int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	(void)argc;
	(void)argv;
	(void)envp;
	
	signal(SIGINT, handle_sigint);
	while (1)
	{
		prompt = get_promt();
		printf("\e[0;32m");
		input = readline(prompt);
		printf("\e[m");
		free(prompt);
		if (!input) // CTRL+D
		{
			printf("Exiting...\n");
			rl_clear_history();
			// free(prompt);
			free(input);
			break;
		}
		if (*input)
			add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}