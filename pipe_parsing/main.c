/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:46:57 by kalicem           #+#    #+#             */
/*   Updated: 2025/01/28 13:14:08 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipeline(t_pipeline *pipeline)
{
	int			i;
	int			j;
	t_command	*cmd;

	if (!pipeline)
		return ;
	i = 0;
	while (pipeline->commands && pipeline->commands[i])
	{
		cmd = pipeline->commands[i];
		printf("Command %d:\n", i + 1);
		if (cmd->args)
		{
			j = 0;
			printf("  Arguments: ");
			while (cmd->args[j])
				printf("'%s' ", cmd->args[j++]);
			printf("\n");
		}
		if (cmd->input_file)
			printf("  Input file: %s\n", cmd->input_file);
		if (cmd->output_file)
			printf("  Out: %s (append: %d)\n", cmd->output_file, cmd->append);
		if (cmd->heredoc)
			printf("  Heredoc: enabled\n");
		i++;
	}
}

int	main(void)
{
	char		*line;
	size_t		len;
	ssize_t		read;
	t_pipeline	*pipeline;
	char		**tokens;

	line = NULL;
	len = 0;
	printf("Enter a command: ");
	read = getline(&line, &len, stdin);
	if (read == -1 || !line)
		return (1);
	line[read - 1] = '\0';
	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		perror("Tokenization failed");
		free(line);
		return (1);
	}
	pipeline = parse_pipeline(tokens);
	print_pipeline(pipeline);
	free_resources(pipeline, tokens, line);
	return (0);
}
//<< echo "hello" | wc >> outfile
//< test.txt cat | wc | ls -l | wc > output.txt
//< test.txt cat | ls -l > outfile.txt