/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:47:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 00:08:18 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*get_data(t_data *new_data)
{
	static t_data	*data = NULL;

	if (new_data)
		data = new_data;
	return (data);
}

t_data_term	*get_term_data(t_data_term *new_term)
{
	static t_data_term term;

	if (new_term) 
		term = *new_term;
	return (&term);
}

int actual_prompt_length(char *str)
{
	int i = 0, len = 0;
	while (str[i])
	{
		if (str[i] == '\033')
		{
			while (str[i] && str[i] != 'm')
			  i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

// int	get_prompt_length(char *prompt)
// {
// 	int		len;
// 	bool	in_escape;

// 	len = 1;
// 	in_escape = false;
// 	while (*prompt)
// 	{
// 		if (*prompt == '\033')
// 			in_escape = true;
// 		else if (in_escape && *prompt == 'm')
// 			in_escape = false;
// 		else if (!in_escape)
// 			len++;
// 		prompt++;
// 	}
// 	return (len);
// }
