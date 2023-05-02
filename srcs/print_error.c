#include "../includes/ft_ping.h"

struct code_error
{
    int type;
    int code;
    char *txt;
} code_error[] = {
    {ICMP_DEST_UNREACH, ICMP_NET_UNREACH, "Destination Net Unreachable"},
    {ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, "Destination Host Unreachable"},
    {ICMP_DEST_UNREACH, ICMP_PROT_UNREACH, "Destination Protocol Unreachable"},
    {ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, "Destination Port Unreachable"},
    {ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, "Fragmentation needed and DF set"},
    {ICMP_DEST_UNREACH, ICMP_SR_FAILED, "Source Route Failed"},
    {ICMP_DEST_UNREACH, ICMP_NET_UNKNOWN, "Network Unknown"},
    {ICMP_DEST_UNREACH, ICMP_HOST_UNKNOWN, "Host Unknown"},
    {ICMP_DEST_UNREACH, ICMP_HOST_ISOLATED, "Host Isolated"},
    {ICMP_DEST_UNREACH, ICMP_NET_UNR_TOS, "Destination Network Unreachable At This TOS"},
    {ICMP_DEST_UNREACH, ICMP_HOST_UNR_TOS, "Destination Host Unreachable At This TOS"},
    {ICMP_DEST_UNREACH, ICMP_PKT_FILTERED, "Packet Filtered"},
    {ICMP_DEST_UNREACH, ICMP_PREC_VIOLATION, "Precedence Violation"},
    {ICMP_DEST_UNREACH, ICMP_PREC_CUTOFF, "Precedence Cutoff"},
    {ICMP_REDIRECT, ICMP_REDIR_NET, "Redirect Network"},
    {ICMP_REDIRECT, ICMP_REDIR_HOST, "Redirect Host"},
    {ICMP_REDIRECT, ICMP_REDIR_NETTOS, "Redirect Type of Service and Network"},
    {ICMP_REDIRECT, ICMP_REDIR_HOSTTOS, "Redirect Type of Service and Host"},
    {ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, "Time to live exceeded"},
    {ICMP_TIME_EXCEEDED, ICMP_EXC_FRAGTIME, "Frag reassembly time exceeded"}
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
        ip->ip_v, ip->ip_hl, ip->ip_tos, ntohs(ip->ip_len), ntohs(ip->ip_id), (ntohs(ip->ip_off) & 0xe000) >> 13, ntohs(ip->ip_off), ip->ip_ttl, ip->ip_p, ntohs(ip->ip_sum));
    
    printf(" %s ", inet_ntoa(*((struct in_addr *)&ip->ip_src)));
    printf(" %s ", inet_ntoa(*((struct in_addr *)&ip->ip_dst)));
    printf("\nICMP: type %u, code %u, size %u, id 0x%02x%02x, seq 0x%02x%02x\n", 
        *data, *(data + 1), ntohs(ip->ip_len) - (ip->ip_hl << 2) , *(data + 4), *(data + 5), *(data + 6), *(data + 7));
}

void            print_icmp_error(int type, int code)
{
    int                 i = 0;
    struct code_error   *tmp;

    tmp = code_error;
    while (i < 20)
    {
        if (tmp->type == type && tmp->code == code)
        {
	        printf ("%s\n", tmp->txt);
	        return ;
        }
        i++;
        tmp++;
    }
    printf ("Unknown Code: %d and Type: %d\n", code, type);
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
    printf("): ");
    print_icmp_error(rec_ping_icmp->type, rec_ping_icmp->code);
    if (t_ping.opt_v)
        verbose_print(rec_ping_icmp);
}