/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sending_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:54:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/08 02:50:37 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	signal_lost(void)
{
	start_colored_output(1, colorcode_by_str("magenta"));
	ft_putstr_fd("Signal lost, resending...\n", 1);
	close_colored_output(1);
	g_client.retry++;
	return ;
}

void	interactive_sending(pid_t pid, t_clientflags flag)
{
	char	*curr_line;
	char	*to_send;

	draw_client();
	ft_putstr_fd("> ", 1);
	curr_line = get_next_line(0);
	while (ft_strncmp(curr_line, "exit\n", 5))
	{
		to_send = ft_substr(curr_line, 0, ft_strlen(curr_line) - (!flag.n));
		sendall(to_send, 0);
		ft_del(to_send);
		ft_del(curr_line);
		init_g_client();
		g_client.pid = pid;
		ft_putstr_fd("> ", 1);
		curr_line = get_next_line(0);
	}
	ft_putstr_fd("\n", 1);
	ft_del(curr_line);
	return ;
}

void	send(t_clientflags flag, char **argv)
{
	if (!flag.count)
		return (sendall(argv[2], 0));
	if ((flag.count == 1 && flag.n))
		return (sendall(argv[3], 1));
	if (flag.i)
		return (interactive_sending(g_client.pid, flag));
	return ;
}
