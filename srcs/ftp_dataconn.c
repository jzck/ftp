/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_dataconn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:30:18 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/02 15:40:05 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		ftp_dataconn(t_ftp *ftp)
{
	char	buf[INET_ADDRSTRLEN];
	int		sock;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ftp_ret(ftp, "150 about to open data conn");
	if (connect(sock, (struct sockaddr*)&ftp->data_sin,
			sizeof(ftp->data_sin)) < 0)
		return(ftp_ret(ftp, "425 can't open data conn"));
	console_msg(1, "dataconn @ %s:%i", inet_ntop(AF_INET, &ftp->data_sin.sin_addr, buf, sizeof(struct sockaddr_in)), ntohs(ftp->data_sin.sin_port));
	return (sock);
}
