/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:06:57 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/17 00:56:13 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include "libft/INCLUDES/libft.h"

typedef struct s_server
{
	unsigned int	current_bit;
	unsigned char	mask;
	char			*msg;
	size_t			msglen;
	int				maxbits;
	int				has_signature;
	int				sigcount;
	unsigned int	len;
}	t_server;

typedef struct s_client
{
	unsigned int	current_bit;
	unsigned char	mask;
	unsigned int	ack;
	int				receive_sig;
	pid_t			pid;
	int				resend;
	int				retry;
}	t_client;

typedef struct s_clientflags
{
	int	i;
	int	n;
	int	h;
	int	count;
}	t_clientflags;

	///* globals *///
extern t_server	g_serv;
extern t_client	g_client;
	///* globals *///

	///* client *///
void			handle_ack(int sig);
void			init_g_client(void);
void			pid_error(void);
void			draw_client(void);
// flags
void			help(void);
t_clientflags	has_flags(int argc, char **argv);
int				right_argcount(t_clientflags flag, int argc);

// sending
void			sig_sending(int sig);
void			char_sending(char c);
void			msg_sending(char *msg);
void			signature_sending(char *msg, int newline);
void			sendall(char *msg, int newline);
void			interactive_sending(pid_t pid, t_clientflags flag);
void			signal_lost(void);
void			send(t_clientflags flag, char **argv);
	///* client *///

	///* server *///
void			init_g_serv(void);
void			get_signature(void);
int				bit_couting(int sig);
void			set_char(void);
	///* server *///

#endif