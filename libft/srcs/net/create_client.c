/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 17:59:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 19:29:49 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	resolve_host(struct sockaddr *s, char *hostname)
{
	struct addrinfo		*result;
	struct addrinfo		hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;
	if (getaddrinfo(hostname, NULL, &hints, &result) != 0)
	{
		perror("getaddrinfo");
		exit(1);
	}
	ft_memcpy(((struct sockaddr_in*)s),
			result->ai_addr, sizeof(struct sockaddr));
	freeaddrinfo(result);
}

int		create_client(char *host, int port, char *protoname)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname(protoname)))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	resolve_host((struct sockaddr*)&sin, host);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (-1);
	return (sock);
}

void	listener(int domain, int sock, int proto,
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
