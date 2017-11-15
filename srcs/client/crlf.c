/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crlf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:52:07 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/15 13:26:43 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

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

	tmp = NULL;
	size = 0;
	while ((ret = recv(sock, buf, CHUNK, 0)) > 0)
	{
		console_msg(2, "recv size=%i", ret);
		buf[ret] = 0;
		*msg = ft_strnew(size + ret);
		ft_memcpy(*msg, tmp, size);
		ft_memcpy(*msg + size, buf, ret);
		ft_memdel(&tmp);
		tmp = *msg;
		size += ret;
	}
	console_msg(2, "raw msg size %i", size);
	return (size);
}

int		ftp_recv(int sock, char **msg)
{
	int		ret;
	char	buf[1024];

	if ((ret = recv(sock, buf, 1024, 0)) < 0)
		return (-1);
	if (ret == 0)
		return (-1);
	console_msg(2, "recv size=%i", ret);
	buf[ret] = 0;
	if (buf[ret - 1] == '\n' && buf[ret - 2] == '\r')
	{
		buf[ret - 2] = 0;
		console_msg(2, "message '%s<CRLF>'", buf);
	}
	else
		console_msg(2, "message '%s'", buf);
	*msg = ft_strdup(buf);
	return (0);
}

int		ftp_sendraw(int sock, char *file, off_t size)
{
	off_t		sent;
	off_t		chunk;
	int			ret;
	
	sent = 0;
	chunk = M / 512;
	while (sent < size)
	{
		if (size - sent < chunk)
			chunk = size - sent;
		ret = send(sock, file, chunk, 0);
		console_msg(2, "---> sendraw error");
		file += chunk;
		sent += chunk;
	}
	console_msg(1, "---> rawsend done size %zu", size);
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
	console_msg(1, "---> %s", crlf_tmp);
	crlf_msg = ft_strjoin(crlf_tmp, "\r\n");
	if ((err = send(sock, crlf_msg, ft_strlen(crlf_msg), 0)) < 0)
	{
		return (err);
	}
	ft_strdel(&crlf_tmp);
	ft_strdel(&crlf_msg);
	return (ft_atoi(msg));
}

int		ftp_msg(t_ftp *ftp, char **msg)
{
	int		code;

	if (ftp_recv(ftp->cmd_sock, msg) < 0)
		return (-1);
	code = ft_atoi(*msg);
	console_msg(0, "<--- %s (%i)", *msg, code);
	return (code);
}

int		ftp_code(t_ftp *ftp)
{
	char	*msg;
	int		code;

	if ((code = ftp_msg(ftp, &msg)) < 0)
		return (-1);
	ft_strdel(&msg);
	return (code);
}
