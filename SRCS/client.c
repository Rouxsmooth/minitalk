/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/15 11:05:30 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

t_client	g_client;
#include <stdio.h>

void printmaskbin(unsigned int mask)
{
	int i;

	i = 7;
	printf("Binary mask: ");
	while (i >= 0)
	{
		printf("%d", (mask >> i) & 1);
		i--;
	}
	printf("\n");
}

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
		usleep(1);
		i++;
		//printf("got to 500? %d\n", i);
	}
	g_client.receivedback++;
	return (0);
}

int	char_sending(char c)
{
	unsigned int	i;
	unsigned int	sent;

	i = 8;
	while (i--)
	{
		sent = sig_sending((c >> i) & 1);
		if (sent == 1)
			return (1);
		if (sent == -1)
			i++;
	}
	printmaskbin((unsigned int) c);
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
	g_client.receivedback = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers"));
	if (argc != 3)
		return (display_error(ft_ternary("input should be \
./client <PID> <MESSAGE>", "too much arguments", argc < 3)));
	g_client.pid = ft_atoi(argv[2]);
	if (g_client.pid < 1)
		return (display_error("invalid server PID"));
	if (msg_sending(argv[1]) == 1)
		return (1);
	signature_sending();
	return (0);
}
