/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sending.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:36:31 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/08 02:45:27 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

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

void	signature_sending(char *msg, int newline)
{
	char	*msglen;

	msglen = ft_itoa(ft_strlen(msg) + newline);
	msg_sending(msglen);
	ft_del(msglen);
	if (g_client.resend)
		return ;
	char_sending('S');
	return ;
}

void	sendall(char *msg, int newline)
{
	if (g_client.retry >= 10)
		return (display_error("Signal definitively lost. This error can come \
from the signature sending logic, or the server acknowledgment algorithm."),
			(void) NULL);
	g_client.resend = 0;
	signature_sending(msg, newline);
	if (g_client.resend)
		return (signal_lost(), sendall(msg, newline));
	g_client.resend = 0;
	msg_sending(msg);
	if (g_client.resend)
		return (signal_lost(), sendall(msg, newline));
	g_client.resend = 0;
	if (newline)
	{
		char_sending('\n');
		if (g_client.resend)
			return (signal_lost(), sendall(msg, newline));
	}
	return (start_colored_output(1, colorcode_by_str("green")),
		ft_putstr_fd("Message received by server!\n", 1),
		close_colored_output(1));
}
