/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_req.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:04:11 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 21:05:34 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		read_req(int sock)
{
	(void)sock;
	return (0);
}

int		ftp_recv(t_ftp *ftp, char **msg)
{
	int		ret;
	char	buf[100];

	if ((ret = recv(ftp->cmd_sock, buf, 100, 0)) < 0)
		return (0);
	buf[ret] = 0;
	if (buf[ret - 1] == '\n' && buf[ret - 2] == '\r')
	{
		buf[ret - 2] = 0;
	}
	else
		console_msg(0, "recv'd non-crlf message!");
	*msg = ft_strdup(buf);
	console_msg(1, "%-5i<--- %s", getpid(), buf);
	return (0);
}

int		ftp_sendto(int sock, struct sockaddr *s, size_t size, char *msg, ...)
{
	int		err;
	char	*crlf_tmp;
	char	*crlf_msg;
	va_list	ap;

	va_start(ap, msg);
	ft_vasprintf(&crlf_tmp, msg, ap);
	crlf_msg = ft_strjoin(crlf_tmp, "\r\n");
	if ((err = sendto(sock, crlf_msg, ft_strlen(crlf_msg), 0, s, size)) < 0)
	{
		return (err);
	}
	console_msg(1, "%-5i---> %s", getpid(), crlf_tmp);
	ft_strdel(&crlf_tmp);
	ft_strdel(&crlf_msg);
	return (ft_atoi(msg));
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
		return (err);
	}
	console_msg(1, "%-5i---> %s", getpid(), crlf_tmp);
	ft_strdel(&crlf_tmp);
	ft_strdel(&crlf_msg);
	return (ft_atoi(msg));
}
