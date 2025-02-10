/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:41:31 by mdemare           #+#    #+#             */
/*   Updated: 2024/12/08 16:57:15 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_formats(char specificator, va_list arg)
{
	int	print_length;

	print_length = 0;
	if (specificator == 'c')
		print_length += ft_print_char((char)va_arg(arg, int));
	else if (specificator == 's')
		print_length += ft_print_str(va_arg(arg, char *));
	else if (specificator == 'd' || specificator == 'i')
		print_length += ft_print_nbr(va_arg(arg, int));
	else if (specificator == '%')
		print_length += ft_print_char('%');
	else if (specificator == 'x')
		print_length += ft_print_hex(va_arg(arg, int), 0);
	else if (specificator == 'X')
		print_length += ft_print_hex(va_arg(arg, int), 1);
	else if (specificator == 'p')
		print_length += ft_print_ptr(va_arg(arg, unsigned long), 1);
	else if (specificator == 'u')
		print_length += ft_print_unsigned(va_arg(arg, unsigned int));
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int		printf_len;
	int		i;
	va_list	arg;

	va_start(arg, str);
	printf_len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			printf_len += ft_formats(str[++i], arg);
		else
			printf_len += ft_print_char(str[i]);
		i++;
	}
	va_end(arg);
	return (printf_len);
}

// int	main(void)
// {
// 	ft_printf("----------------------%%c------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%c\n", 'A'));
// 	printf("taille = %d\n", printf("%c\n", 'A'));
// 	fflush(stdout);
// 	ft_printf("----------------------%%s------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%s\n", "Hello, world!"));
// 	printf("taille = %d\n", printf("%s\n","Hello, world!"));
// 	fflush(stdout);
// 	ft_printf("----------------------%%s2-----------------------\n");
// 	char *str = NULL;
// 	ft_printf("taille = %d\n", ft_printf("%s\n", str));
// 	printf("taille = %d\n", printf("%s\n",str));
// 	fflush(stdout);
// 	ft_printf("----------------------%%p------------------------\n");
// 	int variable = 42;
// 	ft_printf("taille = %d\n",ft_printf("%p\n", NULL));
// 	printf("taille = %d\n",printf("%p\n", NULL));
// 	fflush(stdout);
// 	ft_printf("----------------------%%p2-----------------------\n");
// 	ft_printf("taille = %d\n",ft_printf("%p\n", &variable));
// 	printf("taille = %d\n",printf("%p\n", &variable));
// 	fflush(stdout);
// 	ft_printf("----------------------%%d------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%d\n", 42));
// 	printf("taille = %d\n", printf("%d\n", 42));
// 	fflush(stdout);
// 	ft_printf("----------------------%%i------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%i\n", -42));
// 	printf("taille = %d\n", printf("%i\n",-42));
// 	fflush(stdout);
// 	ft_printf("----------------------%%u------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%u\n", -42));
// 	printf("taille = %d\n", printf("%u\n",-42));
// 	fflush(stdout);
// 	ft_printf("----------------------%%x------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%x\n", -42));
// 	printf("taille = %d\n", printf("%x\n", -42));
// 	fflush(stdout);
// 	ft_printf("----------------------%%X------------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("%X\n", 42));
// 	printf("taille = %d\n", printf("%X\n", 42));
// 	fflush(stdout);
// 	ft_printf("----------------------%%%%-----------------------\n");
// 	ft_printf("taille = %d\n", ft_printf("10%%\n"));
// 	printf("taille = %d\n", printf("10%%\n"));
// 	fflush(stdout);
// 	ft_printf("-------------------------------------------------\n");
// }