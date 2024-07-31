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
        i += put_char(num % 10);
    }
    return i;
}

//handle 's', 'd', 'x' only
int ft_put_args(va_list args, char c)
{
    if (c == '%')
        return put_char('%');
    else if (c == 's')
        return ft_put_str(va_arg(args, char *));
    else if (c == 'd')
        return ft_put_int(va_arg(args, int));
    else if (c == 'x')
        return ft_put_hex(va_arg(args, unsigned int));
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
    int i = 5;
    ft_printf("int i is %d\n", i);
}
