/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:02:51 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 11:39:18 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		create_server(int port, int backlog, char *protoname)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;

	if (!(proto = getprotobyname(protoname)))
		return (-1);
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (-1);
	listen(sock, backlog);
	return (sock);
}
