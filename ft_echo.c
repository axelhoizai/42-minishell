/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/21 18:50:21 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_echo_opt(char *input)
{
	int		i;
	char	*newline;
	
	newline = *utils_parse_args(input);
	if (newline && newline[0] == '-')
	{
		i = 1;
		while (newline[i] && newline[i] == 'n')
			i++;
		if (newline[i] == '\0')
			return ("-n");
	}
	return (newline);
}

int	skip_opt(char **input, int *i)
{
	char	*newline;

	if (input[1])
	{
		newline = handle_echo_opt(input[1]);
		if (ft_strcmp("-n", newline) == 0)
		{
			(*i)++;
			free (newline);
			while (input[*i])
			{
				newline = handle_echo_opt(input[*i]);
				if (ft_strcmp("-n", newline) != 0)
					return (*i);
				(*i)++;
			}
		}
	}
	return (*i);
}

void	ft_echo(char **input)
{
	int		i;

	if (ft_strcmp(input[0], "echo") == 0)
	{
		i = 1;
		i = skip_opt(input, &i);
		if (!input[1] || (ft_strcmp("-n", handle_echo_opt(input[1]))) != 0)
		{
			while (input[i])
			{
				if (input[i] && input[i + 1])
					printf("%s ", input[i]);
				else if (input[i] && !input[i + 1])
					printf("%s", input[i]);
				i++;
			}
			printf("\n");
		}
		else if (ft_strcmp(input[0], "echo") == 0 && (ft_strcmp("-n", handle_echo_opt(input[1]))) == 0)
		{
			while (input[++i])
			{
				if (input[i + 1])
					printf("%s ", input[i]);
				else
					printf("%s", input[i]);
			}
		}
	}
}
