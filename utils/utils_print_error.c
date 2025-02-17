/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:33:31 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 16:47:46 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_construct_error_msg(char *builting, char *arg, char *msg)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("minishell: ");
	if (builting)
	{
		tmp = ft_strjoin(result, builting);
		free(result);
		result = ft_strjoin(tmp, ": ");
		free(tmp);
	}
	if (arg)
	{
		tmp = ft_strjoin(result, arg);
		free(result);
		result = ft_strjoin(tmp, ": ");
		free(tmp);
	}
	if (msg)
	{
		tmp = ft_strjoin(result, msg);
		free(result);
		result = tmp;
	}
	return (result);
}

void	ft_print_error(char *builting, char *arg, char *msg)
{
	char	*result;

	result = ft_construct_error_msg(builting, arg, msg);
	if (result)
	{
		printf("%s\n", result);
		free(result);
	}
}
