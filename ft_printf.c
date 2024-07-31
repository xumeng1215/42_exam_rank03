#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

int ft_printf(char *str, ...);
int ft_put_args(va_list args, char c);
int ft_put_char(char c);
int ft_put_str(char *s);
int ft_put_ptr(void *p);
int ft_put_hex_low(unsigned long n);


int main(void)
{
    int i = 5;
    ft_printf("int i is %d\n", i);
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
        {
            count += write(1, str, 1);
        }
        str++;
    }    
    va_end(args);
    return count;
}

int ft_put_args(va_list args, char c)
{
    if (c == '%')
        return (write (1, '%', 1));
    else if (c == 'c')
        return (ft_put_char(va_arg(args, int)));
    else if (c == 'p')
        return (ft_put_ptr(va_arg(args, void *)));

}

int ft_put_char(char c)
{
    return (write(1, &c, 1));
}

int ft_put_ptr(void *p)
{

}