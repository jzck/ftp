/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:19:41 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/09 14:53:24 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_pasv(t_ftp *ftp)
{
	char	*msg;
	char	**hostport;
	int		code;
	char	buf[INET_ADDRSTRLEN];

	ftp_cmd(ftp, "PASV");
	ftp_recv(ftp->cmd_sock, &msg);
	code = ft_atoi(msg);
	if (code != 227)
	{
		console_msg(2, "PASV failed (%i)", code);
		return (-1);
	}
	hostport = ft_strsplit(msg + 4, ',');
	ftp->dconn.sin.sin_family = AF_INET;
	ftp->dconn.sin.sin_port = htons(256 * ft_atoi(hostport[4])
			+ ft_atoi(hostport[5]));
	ftp->dconn.sin.sin_addr.s_addr = 
		htonl(
		256 * 256 * 256 * ft_atoi(hostport[0])
		+ 256 * 256 * ft_atoi(hostport[1])
		+ 256 * ft_atoi(hostport[2])
		+ ft_atoi(hostport[3]));
	ftp->data_state = DATA_PASV;
	console_msg(1, "remote dconn @ %s:%i",
			inet_ntop(AF_INET, &ftp->dconn.sin.sin_addr, buf, sizeof(struct sockaddr_in)),
			ntohs(ftp->dconn.sin.sin_port));
	return (0);
}
