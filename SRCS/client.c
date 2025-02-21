/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/02/21 17:04:15 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	handle_ack(int sig)
{
	g_client.ack = sig;
}
#include <stdio.h>
int	signature_sending(char *msg)
{
	char	*msglen;

	msglen = ft_itoa(ft_strlen(msg));
	if (msg_sending(msglen) == 1)
		return (ft_del(msglen), 1);
	ft_del(msglen);
	if (char_sending('S') == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	g_client.amount_sent = 0;
	g_client.receive_sig = 0;
	g_client.ack = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers"));
	if (argc != 3)
		return (display_error(ft_ternary("input should be \
./client <PID> <MESSAGE>", "too much arguments", argc < 3)));
	g_client.pid = ft_atoi(argv[1]);
	if (g_client.pid < 1)
		return (display_error("invalid server PID"));
	g_client.msglen = ft_strlen(argv[2]);
	if (signature_sending(argv[2]) == 1)
		return (1);
	if (msg_sending(argv[2]) == 1)
		return (1);
	else
		ft_putstr_fd("Message received by server!\n", 1);
	return (0);
}
