/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:54:57 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:56:01 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static int	pasv_ok(t_ftp *ftp, int sock, struct sockaddr_in sin)
{
	ftp->data_state = DATA_PASV;
	ftp->dconn.sock = sock;
	console_msg(1, "listening on %i (PASV)", ntohs(sin.sin_port));
	return (FTP_RET(ftp, "227 %i,%i,%i,%i,%i,%i",
				(ntohl(sin.sin_addr.s_addr) >> (8 * 3)) & 0xff,
				(ntohl(sin.sin_addr.s_addr) >> (8 * 2)) & 0xff,
				(ntohl(sin.sin_addr.s_addr) >> (8 * 1)) & 0xff,
				(ntohl(sin.sin_addr.s_addr) >> (8 * 0)) & 0xff,
				(ntohs(sin.sin_port) >> (8 * 1)) & 0xff,
				(ntohs(sin.sin_port) >> (8 * 0)) & 0xff));
}

int			cmd_pasv(t_ftp *ftp, char **av)
{
	uint16_t			port;
	int					sock;
	struct sockaddr_in	sin;

	(void)av;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	port = 35000;
	while (++port < USHRT_MAX)
	{
		sin.sin_port = htons(port);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (bind(sock, (const struct sockaddr *)&sin,
					sizeof(struct sockaddr_in)) == 0
				&& listen(sock, 3) == 0)
			return (pasv_ok(ftp, sock, sin));
	}
	return (FTP_RET(ftp, "500 couldn't find local port"));
}
