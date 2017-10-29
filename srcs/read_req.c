/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_req.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:04:11 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:06:53 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		read_req(int sock)
{
	(void)sock;
	return (0);
}

int		ftp_recv(int sock, char buf[], size_t size)
{
	int		ret;

	if ((ret = recv(sock, buf, size, 0)) < 0)
		return (0);
	if (ret >= 2)
		buf[ret - 2] = 0;
	else
		buf[ret] = 0;
	/* req = ntohs(req); */
	console_msg(0, "%-5i<--- %s (%i)", getpid(), buf, ret);
	return (0);
}

int		ftp_send(int sock, char *msg, size_t size)
{
	int err;
	if ((err = send(sock, msg, size, 0)) < 0)
		return (err);
	msg[ft_strlen(msg) - 1] = 0;
	console_msg(0, "%-5i---> %s", getpid(), msg);
	return (0);
}
