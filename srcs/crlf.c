/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_req.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:04:11 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/02 17:09:42 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		read_req(int sock)
{
	(void)sock;
	return (0);
}

int		ftp_recv(int sock, char **msg)
{
	int		ret;
	char	buf[1024];

	if ((ret = recv(sock, buf, 1024, 0)) < 0)
		return (ret);
	buf[ret] = 0;
	if (buf[ret - 1] == '\n' && buf[ret - 2] == '\r')
		buf[ret - 2] = 0;
	else
	{
		return (1);
		console_msg(1, "recv'd non-crlf message!");
	}
	*msg = ft_strdup(buf);
	console_msg(0, "%-5i<--- %s", getpid(), buf);
	return (0);
}

int		ftp_send(int sock, char *msg, ...)
{
	int		err;
	char	*crlf_tmp;
	char	*crlf_msg;
	va_list	ap;

	va_start(ap, msg);
	ft_vasprintf(&crlf_tmp, msg, ap);
	crlf_msg = ft_strjoin(crlf_tmp, "\r\n");
	if ((err = send(sock, crlf_msg, ft_strlen(crlf_msg), 0)) < 0)
	{
		console_msg(1, "%-5i---> send error '%s'", getpid(), crlf_tmp);
		return (err);
	}
	console_msg(0, "%-5i---> %s", getpid(), crlf_tmp);
	ft_strdel(&crlf_tmp);
	ft_strdel(&crlf_msg);
	return (ft_atoi(msg));
}
