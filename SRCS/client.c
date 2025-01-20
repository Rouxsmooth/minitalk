/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/18 22:01:11 by mzaian           ###   ########.fr       */
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

void	receive_signature(int bit)
{
	if (g_client.current_bit < 8)
	{
		g_client.mask |= (bit << (7 - g_client.current_bit));
		g_client.current_bit++;
	}
	if (g_client.current_bit == 8)
	{
		if (g_client.mask == g_client.amount_sent)
			g_client.good_signature = 1;
	}
	return ;
}

void	handle_ack(int sig)
{
	g_client.ack = sig;
	if (g_client.receive_sig == 1)
		receive_signature((sig == SIGUSR2));
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

void	signature_sending(void)
{
	char	*signature;

	signature = ft_itoa(g_client.amount_sent);
	msg_sending("*@");
	msg_sending(signature);
	msg_sending("@*");
	g_client.receive_sig = 1;
	// add a way to receive signature confirmation
	return (free(signature));
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	g_client.amount_sent = 0;
	g_client.receive_sig = 0;
	g_client.good_signature = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (display_error("failed to set up signal handlers"));
	if (argc != 3)
		return (display_error(ft_ternary("input should be \
./client <PID> <MESSAGE>", "too much arguments", argc < 3)));
	g_client.pid = ft_atoi(argv[2]);
	if (g_client.pid < 1)
		return (display_error("invalid server PID"));
	while (!g_client.good_signature)
	{
		if (msg_sending(argv[1]) == 1)
			return (1);
	}
	return (0);
}
