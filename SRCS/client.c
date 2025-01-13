/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/13 18:28:44 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

t_client	g_client;
#include <stdio.h>

void	unacknowledged(void)
{
	return (start_colored_output(1, colorcode_by_str("magenta")),
			ft_printf("Bit reception went wrong, retrying...\n"),
			close_colored_output(1));
}

void	handle_ack(int sig)
{
	g_client.ack = sig;
}

void	sig_sending(int sig)
{
	int	i;

	i = 0;
	if (kill(g_client.pid, (sig * 2) + 10) == -1)
	{
		display_error("Message sending error!");
		return ;
	}
	usleep(1);
	while (!g_client.ack)
	{
		if (i > 500)
			return ;
		usleep(1000);
		i++;
		// printf("got to 500? %d\n", i);
	}
	return ;
}

void	char_sending(char c)
{
	unsigned int	i;

	i = 8;
	while (--i)
		sig_sending((c >> i) & 1);
	return ;
}

void	msg_sending(char *msg)
{
	while (*msg)
	{
		char_sending(*msg);
		msg++;
		g_client.amount_sent++;
	}
	return ;
}

void	signature_sending(void)
{
	char	*signature;

	signature = ft_itoa(g_client.amount_sent);
	msg_sending("*@");
	msg_sending(signature);
	msg_sending("@*");
	// add a way to receive signature confirmation
	return (free(signature));
}

int	main(int argc, char **argv)
{
	struct sigaction sa;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	g_client.amount_sent = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers"));
	if (argc != 3)
		return (display_error(ft_ternary("input should be \
./client <PID> <MESSAGE>", "too much arguments", argc < 3)));
	g_client.pid = ft_atoi(argv[2]);
	if (g_client.pid < 1)
		return (display_error("invalid server PID"));
	msg_sending(argv[1]);
	return (0);
}
