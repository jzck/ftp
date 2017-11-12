/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 17:59:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 17:57:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct addrinfo	*resolve_host(char *hostname, char *port)
{
	struct addrinfo		*result;
	struct addrinfo		hints;
	int					ecode;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if ((ecode = getaddrinfo(hostname, port, &hints, &result)) != 0)
	{
		ft_dprintf(2, "getaddrinfo: %s\n", gai_strerror(ecode));
		exit(1);
	}
	return (result);
}

int				create_tcpclient(char *host, char *port)
{
	struct addrinfo		*ai;
	int					sock;
	struct addrinfo		*first;

	first = resolve_host(host, port);
	ai = first;
	while (ai)
	{
		if ((sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol))
				< 0)
			return (-1);
		if (connect(sock, ai->ai_addr, ai->ai_addrlen) == 0)
			break ;
		close(sock);
		sock = -1;
		ai = ai->ai_next;
	}
	freeaddrinfo(first);
	return (sock);
}

void			listener(int domain, int sock, int proto,
		void (*handler)(void *buf, int bytes, struct sockaddr_in *addr))
{
	int					sd;
	struct sockaddr_in	addr;
	unsigned char		buf[1024];
	int					bytes;
	socklen_t			len;

	len = sizeof(addr);
	sd = socket(domain, sock, proto);
	if (sd < 0)
	{
		perror("listener socket");
		exit(0);
	}
	while (1)
	{
		bzero(buf, sizeof(buf));
		bytes = recvfrom(sd, buf, sizeof(buf), 0,
				(struct sockaddr*)&addr, &len);
		if (bytes > 0 && handler)
			handler(buf, bytes, &addr);
		else
			perror("recvfrom");
	}
	exit(0);
}
