/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crlf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:52:07 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 17:51:32 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	stream mode with file structure --> raw data no EOF
*/
int		ftp_recvraw(int sock, char **msg)
{
	int		ret;
	char	buf[1024];

	if ((ret = recv(sock, buf, 1024, 0)) <= 0)
		return (-1);
	buf[ret] = 0;
	console_msg(2, "%-5i<--- raw msg '%s' (%i)", getpid(), buf, ret);
	*msg = ft_strdup(buf);
	return (0);
}

int		ftp_recv(int sock, char **msg)
{
	int		ret;
	char	buf[1024];

	if ((ret = recv(sock, buf, 1024, 0)) < 0)
		return (ret);
	if (ret == 0)
	{
		console_msg(0, "%-5i client terminated", getpid());
		exit(0);
	}
	buf[ret] = 0;
	if (buf[ret - 1] == '\n' && buf[ret - 2] == '\r')
		buf[ret - 2] = 0;
	else
	{
		console_msg(2, "recv'd non-crlf message '%s'", buf);
		return (1);
	}
	*msg = ft_strdup(buf);
	console_msg(0, "%-5i<--- %s", getpid(), buf);
	return (0);
}

int		ftp_sendraw(int sock, char *msg, ...)
{
	int		err;
	char	*tmp;
	va_list	ap;

	va_start(ap, msg);
	ft_vasprintf(&tmp, msg, ap);
	if ((err = send(sock, tmp, ft_strlen(tmp), 0)) < 0)
	{
		console_msg(1, "%-5i---> send error '%s'", getpid(), tmp);
		return (err);
	}
	console_msg(0, "%-5i---> %s", getpid(), tmp);
	ft_strdel(&tmp);
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
		console_msg(1, "%-5i---> send error '%s'", getpid(), crlf_tmp);
		return (err);
	}
	console_msg(0, "%-5i---> %s", getpid(), crlf_tmp);
	ft_strdel(&crlf_tmp);
	ft_strdel(&crlf_msg);
	return (ft_atoi(msg));
}
