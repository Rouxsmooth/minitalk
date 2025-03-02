/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:36:31 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/02 17:06:33 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	handle_ack(int sig)
{
	g_client.ack = sig;
}

void	sig_sending(int sig)
{
	int	i;

	i = 0;
	g_client.ack = 0;
	if (kill(g_client.pid, (sig * 2) + 10) == -1)
		pid_error();
	usleep(25);
	while (!g_client.ack && i++ <= 500)
		usleep(25);
	if (i > 500)
		g_client.resend = 1;
	return ;
}

void	char_sending(char c)
{
	unsigned int	i;

	i = 8;
	while (i--)
		sig_sending((c >> i) & 1);
	return ;
}

void	msg_sending(char *msg)
{
	while (*msg)
	{
		char_sending(*msg);
		if (g_client.resend)
			return ;
		msg++;
	}
	return ;
}

void	signature_sending(char *msg)
{
	char	*msglen;

	msglen = ft_itoa(ft_strlen(msg));
	msg_sending(msglen);
	ft_del(msglen);
	if (g_client.resend)
		return ;
	char_sending('S');
	return ;
}
