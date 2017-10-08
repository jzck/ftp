/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_req.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:04:11 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:06:53 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		read_req(int sock)
{
	int		req;

	if (read(sock, (char*)&req, sizeof(req)) < 0)
		return (0);
	req = ntohs(req);
	console_msg(0, "%i RECEIVED", req);
	return (req);
}
