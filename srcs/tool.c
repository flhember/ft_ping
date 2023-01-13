#include "../includes/ft_ping.h"

uint16_t checksum(void *b, size_t len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;

	while (len > 1)
	{
		sum += *buf++;
		len = len -2;
	}
	if (len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

void    ft_bzero(void *s, size_t n)
{
    char    *cpy;
    size_t  i;

    i = 0;
    cpy = s;
    while (i < n)
    {
        cpy[i] = '\0';
        i++;
    }
}

void    *ft_memset(void *s, int c, size_t n)
{
    size_t  i;
    char    *cpy;

    cpy = s;
    i = 0;
    while (i < n)
    {
        cpy[i] = (unsigned char)c;
        i++;
    }
    return (cpy);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}