/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/23 18:28:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*handle_n(char *flag)
// {
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	if (flag[0] == '-')
// 	{
// 		while (flag[i] && flag[i] == 'n')
// 			i++;
// 		if (flag[i] == '\0')
// 			return (ft_strdup("-n"));
// 	}
// 	return (ft_strdup(flag));
// }

// char	*parse_arg(char *arg)
// {
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	*tmp3;
// 	int		i;
	
// 	i = 0;
// 	if (ft_strchr(arg, '"') || ft_strchr(arg, '\''))
// 	{
// 		tmp1 = ft_strdup(arg);
// 		tmp2 = parse_quote(tmp1);
// 		free(tmp1);
// 		tmp3 = handle_n(tmp2);
// 		if (tmp3)
// 		{
// 			free(tmp2);
// 			tmp2 = ft_strdup(tmp3);
// 			free(tmp3);
// 		}
// 		return (tmp2);
// 	}
// 	return (handle_n(arg));
// }

// builtin_tab[i] = parse_arg(argv[i]);
// 		if (((ft_strstr(argv[i - 1], "-n") != NULL) || i == 1) 
// 				&& (ft_strcmp("-n", argv[i]) != 0 && argv[i][0] == '-'))
// 			builtin_tab[i] = handle_n(argv[i]);
// 		printf("builtin_tab[%d] = %s\n", i, builtin_tab[i]);

char	*handle_n(char *flag)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (ft_strcmp("-n", flag) != 0 && flag[0] == '-')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
			return (ft_strdup("-n"));
	}
	return (flag);
}

char	*parse_arg(char *arg)
{
	int		i;

	i = 0;
	if (ft_strchr(arg, '"') || ft_strchr(arg, '\''))
		return (parse_quote(arg));
	return (arg);
}

// char	**ft_echo_tab(int argc, char **argv)
// {
// 	int		i;
// 	char	**builtin_tab;

// 	i = 0;
// 	print_tab(argv);
// 	builtin_tab = malloc(sizeof (char *) * (argc + 1));
// 	while (argv[i])
// 	{
// 		builtin_tab[i] = parse_arg(argv[i]);
// 		printf("arg : %s\n", builtin_tab[i]);
// 		i++;
// 	}
// 	builtin_tab[i] = NULL;
// 	return (builtin_tab);
// }

char	**ft_echo_tab(int argc, char **argv)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = malloc(sizeof(char *) * (argc + 1));
	if (!builtin_tab)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		builtin_tab[i] = ft_strdup(argv[i]);
		builtin_tab[i] = parse_arg(argv[i]);
		if (((i > 0 && (ft_strstr(builtin_tab[i - 1], "-n") != NULL)) || i == 1) 
				&& (ft_strcmp("-n", builtin_tab[i]) != 0 && builtin_tab[i][0] == '-'))
			builtin_tab[i] = handle_n(builtin_tab[i]);
		printf("builtin_tab[%d] = %s\n", i, builtin_tab[i]);
		i++;
	}
	builtin_tab[i] = NULL;
	return (builtin_tab);
}

char	*parse_dollar(char *arg, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*result;
	int i;

	i = 0;
	while (arg)
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			break ;
		i++;
	}
	tmp = ft_substr(arg, 0, i);
	tmp2 = ft_substr(arg, i + 2, ft_strlen(arg));
	tmp3 = ft_strjoin(tmp, ft_itoa(data->exit_code));
	result = ft_strjoin(tmp3, tmp2);
	free(tmp);
	free(tmp2);
	free(tmp3);	
	if (ft_strstr(result, "$?"))
		return (parse_dollar(result, data));
	return (result);
}

void	print_echo(char	**builtin_tab, t_data *data, int *i)
{
	while (builtin_tab[*i])
	{
		if (ft_strstr(builtin_tab[*i], "$?"))
			builtin_tab[*i] = parse_dollar(builtin_tab[*i], data);
		if (builtin_tab[*i] && builtin_tab[*i + 1])
			printf("%s ", builtin_tab[*i]);
		else if (builtin_tab[*i] && !builtin_tab[*i + 1])
			printf("%s", builtin_tab[*i]);
		(*i)++;
	}
}

void	ft_echo(int argc, char **argv, t_data *data)
{
	int		i;
	char	**builtin_tab;

	builtin_tab = ft_echo_tab(argc, argv);
	if (ft_strcmp(builtin_tab[0], "echo") == 0)
	{
		if (!builtin_tab[1] || (ft_strcmp("-n", builtin_tab[1])) != 0)
		{
			i = 1;
			print_echo(builtin_tab, data, &i);
			printf("\n");
		}
		else if (ft_strcmp(builtin_tab[0], "echo") == 0 && (ft_strcmp("-n", builtin_tab[1])) == 0)
		{
			i = 1;
			while (builtin_tab[i] && (ft_strcmp("-n", builtin_tab[i])) == 0)
				i++;
			print_echo(builtin_tab, data, &i);
		}
	}
	free_tab(builtin_tab);
}



// builtin_tab[i] = parse_arg(argv[i]);
// 		if (((ft_strstr(argv[i - 1], "-n") != NULL) || i == 1) 
// 				&& (ft_strcmp("-n", argv[i]) != 0 && argv[i][0] == '-'))
// 			builtin_tab[i] = handle_n(argv[i]);
// 		printf("builtin_tab[%d] = %s\n", i, builtin_tab[i]);