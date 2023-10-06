#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

static void	ft_putchar_counter(char c, int *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

static void	ft_putstr_counter(char *str, int *counter)
{
	int	i;

	i = -1;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		*counter = *counter + 6;
		return ;
	}
	while (str[++i])
		ft_putchar_counter(str[i], counter);
}

static void	ft_putnbr_counter(int nb, int *counter)
{
	//INT_MIN -> -2147483648
	if (nb == INT_MIN)
	{
		ft_putstr_counter("-2147483648", counter);
		return ;
	}
	if (nb < 0)
	{
		nb = nb * (-1);
		ft_putchar_counter('-', counter);
	}
	if (nb > 9)
		ft_putnbr_counter(nb / 10, counter);
	nb = nb % 10 + '0';
	ft_putchar_counter(nb, counter);
}

static void	ft_puthex_counter(unsigned int nb, int *counter)
{
	// tenemos un int, lo transf en hexadecimal (base 16)
	char	base;

	base = "0123456789abcdef" [nb % 16];
	if (nb > 15)
		ft_puthex_counter(nb / 16, counter);
	ft_putchar_counter(base, counter);
}

static void	ft_menu(va_list argmts, char format, int *counter)
{
	if (format == 's')
		ft_putstr_counter(va_arg(argmts, char *), counter);
	if (format == 'd')
		ft_putnbr_counter(va_arg(argmts, int), counter);
	if (format == 'x')
		ft_puthex_counter(va_arg(argmts, unsigned int), counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	argmts;
	int			counter;

	counter = 0;
	va_start(argmts, format);
	while (*format)
	{
		if (*format != '%')
			ft_putchar_counter(*format, &counter);
		else
		{
			format++;
			if (!*format)
				break;
			ft_menu(argmts, *format, &counter);
		}
		format++;
	}
	va_end(argmts);
	return (counter);
}

int	main(int argc, char **argv)
{
	int	i;
	int	num = -2147483648;
	char *str = NULL;

	i = 0;
	if (argc != 2)
		return (0);
	i = ft_printf("F - %s\n", str);
	ft_printf("%d\n", i);
	i = ft_printf("F - un string  param  %s\n", argv[1]);
	ft_printf("%d\n", i);
	i = ft_printf("F - un numero         %d\n", num);
	ft_printf("%d\n", i);
	i = ft_printf("F - un hexadecimal    %x\n", 42);
	ft_printf("%d\n", i);
	i = ft_printf("F - de todo           %s + %d + %x\n", "hola", 42, 42);
	ft_printf("%d\n", i);
	i = ft_printf("F -									%s\n", "toto");
	ft_printf("%d\n", i);
	i = ft_printf("F - 									Magic %s is %d\n", "number", 42);
	ft_printf("%d\n", i);
	i = ft_printf("F - 									Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("%d\n\n\n", i);

//*********************************************************

	i = printf("P - %s\n", str);
	printf("%d\n", i);	
	i = printf("P - un string         %s\n", argv[1]);
	printf("%d\n", i);
	i = printf("P - un numero         %d\n", num);
	printf("%d\n", i);
	i = printf("P - un hexadecimal    %x\n", 42);
	printf("%d\n", i);
	i = printf("P - de todo           %s + %d + %x\n", "hola", 42, 42);
	printf("%d\n", i);
	i = printf("P -										%s\n", "toto");
	printf("%d\n", i);
	i = printf("P -										Magic %s is %d\n", "number", 42);
	printf("%d\n", i);
	i = printf("P -										Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", i);
	return (0);
}
