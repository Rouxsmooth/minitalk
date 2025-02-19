/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:36:31 by mzaian            #+#    #+#             */
/*   Updated: 2025/02/19 11:15:48 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

int	sig_sending(int sig)
{
	int	i;

	i = 0;
	g_client.ack = 0;
	if (kill(g_client.pid, (sig * 2) + 10) == -1)
		return (display_error("wrong pid"));
	usleep(1);
	while (!g_client.ack)
	{
		if (i > 500)
			return (-1);
		usleep(3);
		i++;
	}
	return (0);
}

int	char_sending(char c)
{
	unsigned int	i;
	int				sent;

	i = 8;
	while (i--)
	{
		sent = sig_sending((c >> i) & 1);
		if (sent == 1)
			return (1);
		if (sent == -1)
			i++;
	}
	return (0);
}

int	msg_sending(char *msg)
{
	while (*msg)
	{
		if (char_sending(*msg) == 1)
			return (1);
		msg++;
		g_client.amount_sent++;
	}
	return (0);
}
