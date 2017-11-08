/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:54:57 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 17:15:09 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_pasv(t_ftp *ftp, char **av)
{
	uint16_t	port;
	int			sock;
	struct sockaddr_in	sin;

	(void)av;
	return (ftp_ret(ftp, "502 not implemented"));
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
		{
			ftp->data_state = DATA_PASV;
			ftp->dconn.sock = sock;
			console_msg(1, "listening on %i (PASV)", port);
			return (ftp_ret(ftp, "227 %i,%i,%i,%i,%i,%i",
						(ntohl(sin.sin_addr.s_addr) >> (8*3)) & 0xff,
						(ntohl(sin.sin_addr.s_addr) >> (8*2)) & 0xff,
						(ntohl(sin.sin_addr.s_addr) >> (8*1)) & 0xff,
						(ntohl(sin.sin_addr.s_addr) >> (8*0)) & 0xff,
						(ntohs(sin.sin_port) >> (8*1)) & 0xff,
						(ntohs(sin.sin_port) >> (8*0)) & 0xff
						));
		}
	}
	return (ftp_ret(ftp, "500 couldn't find local port"));
}
