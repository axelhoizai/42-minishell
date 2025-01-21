/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/21 13:59:48 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **input)
{
	int	i;

	if (ft_strcmp(input[0], "echo") == 0 && (!input[1] || ft_strcmp(input[1], "-n") != 0))
	{
		i = 0;
		while (input[++i])
		{
			if (input[i + 1])
				printf("%s ", input[i]);
			else
				printf("%s", input[i]);
		}
		printf("\n");
	}
	else if (ft_strcmp(input[0], "echo") == 0 && (ft_strcmp(input[1], "-n")) == 0)
	{
		i = 1;
		while (input[++i])
		{
			if (input[i + 1])
				printf("%s ", input[i]);
			else
				printf("%s", input[i]);
		}
	}
}
