/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:46:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 14:18:19 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	chk_next_tok(char **tokens, int *i)
{
	char	*trim2;

	trim2 = ft_strtrim(tokens[*i + 1], "<|>");
	if (trim2[0] == '\0' && !tokens[*i + 2])
	{
		ft_print_error(NULL, NULL, MSG_ERROR_SYNTAX);
		free(trim2);
		return (false);
	}
	free(trim2);
	return (true);
}

bool	check_redir_pipe(char **tokens)
{
	int		i;
	char	*trim;

	i = 0;
	while (tokens[i])
	{
		trim = ft_strtrim(tokens[i], "<|>");
		if (tokens[i][0] && trim[0] == '\0' && ft_strncmp(tokens[i], "||", 2))
		{
			if (!tokens[i + 1])
			{
				ft_print_error(NULL, NULL, MSG_ERROR_SYNTAX);
				return (free(trim), false);
			}
			else if (chk_next_tok(tokens, &i) == false)
			{
				free(trim);
				return (false);
			}
		}
		i++;
		free(trim);
	}
	return (true);
}

bool	is_pipe(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '|'))
		{
			free_tab(argv);
			return (true);
		}
		i++;
	}
	free_tab(argv);
	return (false);
}

bool	is_token_pipe(char *token)
{
	if (!token)
		return (false);
	return (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0);
}

bool	is_builtin(t_command *cmd)
{
	if (cmd->args)
	{
		if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "env") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (true);
		else if (ft_strcmp(cmd->args[0], "clear") == 0)
			return (true);
	}
	return (false);
}
