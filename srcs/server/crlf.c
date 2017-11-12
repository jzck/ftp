/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crlf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:52:07 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 15:13:42 by jhalford         ###   ########.fr       */
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
	void	*tmp;
	int		size;

	tmp = NULL;
	size = 0;
	while ((ret = recv(sock, buf, 1024, 0)) > 0)
	{
		buf[ret] = 0;
		*msg = ft_strnew(size + ret);
		ft_memcpy(*msg, tmp, size);
		ft_memcpy(*msg + size, buf, ret);
		ft_memdel(&tmp);
		tmp = *msg;
		size += ret;
	}
	console_msg(2, "%-5i<--- raw msg size %i", getpid(), size);
	return (size);
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
	else if (buf[ret - 1] == '\n')
		buf[ret - 1] = 0;
	else
	{
		console_msg(2, "recv'd non-crlf/lf message '%s'", buf);
		return (1);
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
