/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_crlf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 12:45:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/20 13:23:21 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

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
	{
		console_msg(0, "server terminated");
		exit(0);
	}
	code = ft_atoi(*msg);
	console_msg(0, "<--- %s", *msg);
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
