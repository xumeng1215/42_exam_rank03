#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

//basic put_char
int put_char(char c)
{
	return (write(1, &c, 1));
}

//output string
int ft_put_str(char *str)
{
    int i = 0;

    while(str[i])
    {
        put_char(str[i]);
        i++;
    }
    return i;
}

//output integer
//need to consider the int range
int ft_put_int(int num)
{
    int i = 0;

    if(num == -2147483648)
        return (ft_put_str("-2147483648"));
    if(num < 0)
    {
        i += put_char('-');
        num = -1 * num;
    }
    if(num < 10)
        i += put_char(num + '0');
    else
    {
        i += ft_put_int(num / 10);
        i += put_char(num % 10 + '0');
    }
    return i;
}

//output number in hex format
//taking unsigned int, otherwise won't work
int ft_put_hex(unsigned int num)
{
    int i = 0;
    char set[16] = "0123456789abcdef";

    if (num < 16)
        i += put_char(set[num]);
    else
    {
        i += ft_put_hex(num / 16);
        i += put_char(set[num % 16]);
    }
    return i;
}

//handle 's', 'd', 'x' only
int ft_put_args(va_list args, char c)
{
    if (c == '%')
        return (put_char('%'));
    else if (c == 's')
        return (ft_put_str(va_arg(args, char *)));
    else if (c == 'd')
        return (ft_put_int(va_arg(args, int)));
    else if (c == 'x')
        return (ft_put_hex(va_arg(args, unsigned int)));
    else
        return -1;
}

int ft_printf(char *str, ...)
{
    va_list args;
    va_start(args, str);
    int count = 0;

    while(*str)
    {
        if(*str == '%')
        {
            count += ft_put_args(args, *(str+1));
            str++;
        }
        else
            count += put_char(*str);
        str++;
    }
    va_end(args);
    return count;
}

int main(void)
{
    int i = 2147483647;
    int a, b;
    char *s = "hello";

    a = ft_printf("%s\n", s);
    b = printf("%s\n", s);
    printf("a %d, b %d\n", a, b);

    a = ft_printf("%d\n", i);
    b = printf("%d\n", i);
    printf("a %d, b %d\n", a, b);

    a = ft_printf("%x\n", i);
    b = printf("%x\n", i);
    printf("a %d, b %d\n", a, b);
}
