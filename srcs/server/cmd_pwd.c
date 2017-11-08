/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:39:01 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/02 14:18:58 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_pwd(t_ftp *ftp, char **av)
{
	char	path[200];

	(void)av;
	getcwd(path, 200);
	ftp_ret(ftp, "257 \"%s\"", path);
	return (0);
}
