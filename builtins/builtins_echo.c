/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:23 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/22 17:04:21 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo -n "ho"l"a""

// cd "ho""la" ok
// echo = 'ho' 'la' pas ok
//echo -n "ho""la" ok

// cd "ho"la" ok
// echo = 'ho' 'la' '' pas ok
//echo -n  "ho"la" ok

// cd "ho"l"a" pas ok
// echo = 'ho' 'l' 'a' pas ok

// cd "ho"l"a" pas ok
// echo = 'ho' 'l' 'a' pas ok
void	print_tab(char **tab) 
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("[%d] : \'%s\'\n", i, tab[i]);
		i++;
	}
}

char	*handle_n(char *flag)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (flag[0] == '-')
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (flag[i] == '\0')
		{
			free(flag);
			flag = ft_strdup("-n");
		}
	}
	return (flag);
}

int		ft_count_simgle(char *arg)
{
	int	count_simgle;
	int	i;
	
	count_simgle = 0;
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\'')
			count_simgle++;
		i++;
	}
	printf("count_single = %d\n", count_simgle);
	if (count_simgle % 2 == 1)
		count_simgle -=1;
	printf("count_singlebis = %d\n", count_simgle);
	return (count_simgle);
}

int		ft_count_double(char *arg)
{
	int	count_double;
	int	i;
	
	count_double = 0;
	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\"')
			count_double++;
		i++;
	}
	if (count_double % 2 == 1)
		count_double -=1;
	
	return (count_double);
}

//echo "hell"o'see'you""again""""""""'
char	*parse_quote(char *arg)
{
	char	*tmp1;
	int		j;
	int		count_double;
	int		count_simgle;

	j = 0;
	count_simgle = ft_count_simgle(arg);
	count_double = ft_count_double(arg);
	tmp1 = ft_calloc(ft_strlen(arg) + 1, 1);
	while (*arg)
	{
		while (count_double > 0 && *arg == '"')
		{
			count_double -= 1;
			arg++;
		}
		while (count_simgle > 0 && *arg == '\'')
		{
			count_simgle -= 1;
			arg++;
		}
		tmp1[j++] = *arg;
		arg++;
	}
	return (tmp1);
}

// char	*parse_arg(char *arg)
// {
// 	// char	**tmp1;
// 	int		i;

// 	i = 0;
// 	arg = parse_quote(arg);
// 	// tmp1 = utils_parse_args(arg);
// 	// free(arg);
// 	// while (tmp1[i])
// 	// 	i++;
// 	// if (i > 1)
// 	// 	arg = ft_strjoin(tmp1[0], tmp1[1]);
// 	// else
// 	// 	arg = ft_strdup(tmp1[0]);
// 	// free_tab(tmp1);
// 	return (arg);
// }

void	ft_echo(int argc,char **argv)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	// char	**parsed_arg;

	// parsed_arg = NULL;
	// char	**builtin_tab;
	// char	*arg;
	// char	*flag;

	// flag = NULL;
	// if (argc  > 1)
	// 	flag = *handle_n(argv[1]);
	// if (ft_strcmp("-n", flag) == 0)
	// {
	// 	printf("argv[1] = %s\n", flag);
	// 	i = 2;
	// }
	// else
	i = 0;
	(void)argc;
	print_tab(argv);
	while (argv[i])
	{
		tmp1 = ft_strdup(argv[i]);
		tmp2 = parse_quote(tmp1); //probleme
		tmp3 = handle_n(tmp2); //probleme echo "hell"o'see'you""again""""""""' 
		printf("tmp3 = %s\n", tmp3); //echo -n  "ho"la"
		if (tmp1)
			free(tmp1);
		// if (tmp2)
		// 	free(tmp2);
		// if (tmp3)
		// 	free(tmp3);
		i++;
	}
	
	// builtin_tab = handle_n(input);
	// if (ft_strcmp(builtin_tab[0], "echo") == 0)
	// {
	// 	if (!builtin_tab[1] || (ft_strcmp("-n", builtin_tab[1])) != 0)
	// 	{
	// 		i = 1;
	// 		while (builtin_tab[i])
	// 		{
	// 			if (builtin_tab[i] && builtin_tab[i + 1])
	// 				printf("%s ", builtin_tab[i]);
	// 			else if (builtin_tab[i] && !builtin_tab[i + 1])
	// 				printf("%s", builtin_tab[i]);
	// 			i++;
	// 		}
	// 		printf("\n");
	// 	}
	// 	else if (ft_strcmp(builtin_tab[0], "echo") == 0 && (ft_strcmp("-n", builtin_tab[1])) == 0)
	// 	{
	// 		i = 1;
	// 		while (builtin_tab[i] && (ft_strcmp("-n", builtin_tab[i])) == 0)
	// 			i++;
	// 		while (builtin_tab[i])
	// 		{
	// 			if (builtin_tab[i + 1])
	// 				printf("\'%s\' ", builtin_tab[i]);
	// 			else
	// 				printf("\'%s\'", builtin_tab[i]);
	// 			i++;
	// 		}
	// 	}
	// }
	// free(flag);
}
