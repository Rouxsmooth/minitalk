/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:54:54 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/08 02:48:44 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	handle_ack(int sig)
{
	g_client.ack = sig;
}

void	pid_error(void)
{
	if (g_client.retry)
		display_error("Invalid PID, server probably closed.");
	else
		display_error("Invalid PID");
	exit(0);
}

void	init_g_client(void)
{
	g_client.current_bit = 0;
	g_client.mask = 0;
	g_client.ack = 0;
	g_client.receive_sig = 0;
	g_client.pid = 0;
	g_client.resend = 0;
	g_client.retry = 0;
}
