/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_epsv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 11:13:03 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:37:44 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_epsv(t_ftp *ftp, char **av)
{
	uint16_t			port;
	int					sock;
	struct sockaddr_in6	sin;

	(void)av;
	sin.sin6_family = AF_INET6;
	sin.sin6_addr = in6addr_any;
	port = 35000;
	while (++port < USHRT_MAX)
	{
		sin.sin6_port = htons(port);
		sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
		if (bind(sock, (const struct sockaddr *)&sin,
					sizeof(struct sockaddr_in6)) == 0
			&& listen(sock, 3) == 0)
		{
			ftp->data_state = DATA_EPSV;
			ftp->dconn.sock = sock;
			console_msg(1, "listening on %i (EPSV)", port);
			return (FTP_RET(ftp, "229 (|||%hu|)", ntohs(sin.sin6_port)));
		}
	}
	return (FTP_RET(ftp, "500 couldn't find local port"));
}
