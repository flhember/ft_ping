#include "../includes/ft_ping.h"

static const char       *error_icmp[] = {
    "",
    "",
    "",
    "Destination Net Unreachable"
};

void            verbose_print(struct icmphdr *icmp)
{
    size_t          i = 0;
    struct ip       *ip = (struct ip *) ((char *)icmp + sizeof(icmp));
    unsigned char   *data = (unsigned char *) ip + sizeof(*ip);

    printf("IP Hdr Dump:\n");
    while (i < sizeof(*ip))
    {
        printf("%02x%s", *((unsigned char *)ip + i), (i % 2) ? " " : "");
        i++;
    }
    printf("\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst     Data\n");
    printf(" %01x  %01x  %02x %04x %04x   %1x %04x  %02x  %02x %04x", 
        ip->ip_v, ip->ip_hl, ip->ip_tos, ip->ip_len, ntohs(ip->ip_id), (ntohs(ip->ip_off) & 0xe000) >> 13, ntohs(ip->ip_off), ip->ip_ttl, ip->ip_p, ntohs(ip->ip_sum));
    
    printf(" %s ", inet_ntoa(*((struct in_addr *)&ip->ip_src)));
    printf(" %s ", inet_ntoa(*((struct in_addr *)&ip->ip_dst)));
    printf("\nICMP: type %u, code %u, size %u, id 0x%02x%02x, seq 0x%02x%02x\n", 
        *data, *(data + 1), ntohs(ip->ip_len) - (ip->ip_hl << 2) , *(data + 4), *(data + 5), *(data + 6), *(data + 7));
}

void            print_error_rec(struct icmphdr *rec_ping_icmp, struct iphdr	*rec_ping_ip, ssize_t bytes_rec)
{
    char buf[256];
    struct sockaddr_in tmp_addr;

    tmp_addr.sin_family = AF_INET;
    tmp_addr.sin_addr.s_addr = rec_ping_ip->saddr;
    getnameinfo((struct sockaddr *)&tmp_addr, sizeof(struct sockaddr_in), buf, sizeof(buf), NULL, 0, NI_NAMEREQD);
    printf("%zu bytes from %s (", bytes_rec - sizeof(struct iphdr), buf);
    return_addr(buf);
    printf("): %s\n", error_icmp[rec_ping_icmp->type]);

	printf("Error Packet received with ICMP type %d\n", rec_ping_icmp->type);             // for debug

    if (t_ping.opt_v)
        verbose_print(rec_ping_icmp);

}