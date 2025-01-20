/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 18:44:54 by mdemare          ###   ########.fr       */
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

void	handle_sigquit(int sig) //revoir pour 'ctrl+\'
{
	(void)sig;
}

void	get_promt()
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
	printf("\e[0;44m");
	printf("%s\n", prompt);
	free (prompt);
	printf("\e[m");
}

int	main(int ac, char **envp)
{
	// int		argc;
	char	**argv;
	char	*input;
	(void)envp;
	(void)ac;
	
	signal(SIGINT, handle_sigint);
	while (1)
	{
		if (signal(SIGQUIT, handle_sigquit) == SIG_ERR) //revoir pour 'ctrl+\'
			;		
		get_promt();
		input = readline(" % ");
		if (!input) // CTRL+D
		{
			printf("Exiting...\n");
			rl_clear_history();
			free(input);
			break;
		}
		if (*input)
			add_history(input);
		// printf("You entered: %s\n", input);
		argv = ft_split(input, ' ');
		free(input);
		free_tab(argv);
	}
	return (0);
}
