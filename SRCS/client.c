/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/02 16:56:30 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	pid_error(void)
{
	display_error("wrong pid");
	exit(0);
}

void	sendall(char *msg)
{
	if (g_client.retry >= 10)
		return (display_error("Signal definitively lost. This error can come \
from the signature sending logic, or the server acknowledgment algorithm."),
			(void) NULL);
	g_client.resend = 0;
	signature_sending(msg);
	if (g_client.resend)
		return (start_colored_output(1, colorcode_by_str("magenta")),
			ft_putstr_fd("Signal lost, resending...\n", 1),
			close_colored_output(1), g_client.retry++, sendall(msg));
	g_client.resend = 0;
	msg_sending(msg);
	if (g_client.resend)
		return (start_colored_output(1, colorcode_by_str("magenta")),
			ft_putstr_fd("Signal lost, resending...\n", 1),
			close_colored_output(1), g_client.retry++, sendall(msg));
	return (start_colored_output(1, colorcode_by_str("green")),
		ft_putstr_fd("Message received by server!\n", 1),
		close_colored_output(1));
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers"));
	if (argc != 3)
		return (display_error(ft_ternary("input should be \
./client <PID> <MESSAGE>", "too much arguments", argc < 3)));
	g_client.pid = ft_atoi(argv[1]);
	if (g_client.pid < 1)
		return (display_error("invalid server PID"));
	sendall(argv[2]);
	return (0);
}
