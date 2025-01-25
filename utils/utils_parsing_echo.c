/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:29:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/25 16:33:52 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pid(void)
{
	int		pid;
	char	*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	return (pid_str);
}

char	*parse_dollar_double(char *arg)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		i;

	i = 0;
	while (arg)
	{
		if (arg[i] == '$' && arg[i + 1] == '$')
			break ;
		i++;
	}
	tmp1 = ft_substr(arg, 0, i);
	tmp2 = pid();
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_substr(arg, i + 2, ft_strlen(arg));
	free(arg);
	arg = ft_strjoin(tmp3, tmp1);
	free(tmp1);
	free(tmp3);
	if (ft_strstr(arg, "$?"))
		return (parse_dollar(arg));
	return (arg);
}
