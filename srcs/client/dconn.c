/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dconn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:55:15 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 18:48:44 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static int	dconn_open_pasv(t_ftp *ftp)
{
	int		sock;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (struct sockaddr*)&ftp->dconn.sin,
				sizeof(struct sockaddr_in)) < 0)
	{
		return (-1);
	}
	ftp->d_sock = sock;
	return (0);
}

static int	dconn_open_actv(t_ftp *ftp)
{
	int		sock;

	if ((sock = accept(ftp->dconn.sock, NULL, NULL)) < 0)
	{
		return (-1);
	}
	ftp->d_sock = sock;
	return (0);
}

int			dconn_init(t_ftp *ftp)
{
	if (ftp->data_state == DATA_NONE)
	{
		if (cli_pasv(ftp) < 0)
			return (-1);
	}
	return (0);
}

int			dconn_open(t_ftp *ftp)
{
	int		code;

	code = ftp_code(ftp);
	if (code == 150)
	{
		if (ftp->data_state == DATA_ACTV)
			return (dconn_open_actv(ftp));
		else if (ftp->data_state == DATA_PASV)
			return (dconn_open_pasv(ftp));
	}
	else if (code == 125)
		return (0);
	return (-1);
}

int			dconn_close(t_ftp *ftp)
{
	int		code;

	DG("check");
	if ((code = ftp_code(ftp)) < 0)
		return (-1);
	DG("check");
	if (code == 226)
	{
		if (ftp->d_sock != 0)
		{
			close(ftp->d_sock);
			ftp->d_sock = 0;
		}
		ftp->data_state = DATA_NONE;
		console_msg(1, "dataconn closed");
	}
	else
	{
		console_msg(1, "keeping dataconn alive");
	}
	return (0);
}
