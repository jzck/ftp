/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:18:31 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/02 21:40:32 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

#define FTP_CLIENT_USAGE	"%s <addr> <port>"

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (-1);
	return (sock);
}

int		main(int ac, char **av)
{
	int 				port;
	int					sock;

	if (ac != 3)
		ft_usage(FTP_CLIENT_USAGE, av[0]);
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port)) < 0)
	{
		perror(av[0]);
		return (1);
	}
	write(sock, "bonjour\n", 8);
	close(sock);
	return (0);
}
