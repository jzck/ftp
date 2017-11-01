/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:15:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 21:06:41 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		ftp_login(t_ftp *ftp)
{
	char	*msg;

	chdir("data");
	ftp_ret(ftp, "220 ready for user");
	ftp_recv(ftp, &msg);
	ftp_ret(ftp, "230 user logged in, proceed");
	return (0);


	if (ft_strncmp(msg, "USER ", 5) != 0)
		console_msg(0, "expected USER");
	if (ft_strncmp(msg + 5, "jack", 4) != 0)
		ftp_ret(ftp, "530 user not logged in");
	else
		ftp_ret(ftp, "331 user name ok, send passwd");
	ftp_recv(ftp, &msg);
	return (0);
}
