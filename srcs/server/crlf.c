/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crlf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:52:07 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/20 13:21:25 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	stream mode with file structure --> raw data no EOF
*/

#define M		(1024 * 1024)
#define CHUNK	(M)

int		ftp_recvraw(int sock, char **msg)
{
	int		ret;
	char	buf[CHUNK];
	void	*tmp;
	int		size;

	size = 0;
	tmp = NULL;
	console_msg(0, "starting download...");
	while ((ret = recv(sock, buf, CHUNK, 0)) > 0)
	{
		buf[ret] = 0;
		*msg = ft_strnew(size + ret);
		ft_memcpy(*msg, tmp, size);
		ft_memcpy(*msg + size, buf, ret);
		ft_memdel(&tmp);
		tmp = *msg;
		size += ret;
	}
	console_msg(2, "<--- raw msg size %i", size);
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
		console_msg(0, "client terminated");
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
	console_msg(0, "<--- %s", buf);
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
		console_msg(1, "---> send error '%s'", crlf_tmp);
		return (err);
	}
	console_msg(0, "---> %s", crlf_tmp);
	ft_strdel(&crlf_tmp);
	ft_strdel(&crlf_msg);
	return (ft_atoi(msg));
}
