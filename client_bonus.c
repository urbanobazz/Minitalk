/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:42:42 by ubazzane          #+#    #+#             */
/*   Updated: 2024/01/22 15:25:45 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	send_bit(int pid, char *str);
static void	sig_confirm(int sig);

int	main(int argc, char **argv)
{
	int					i;
	struct sigaction	sig_act;

	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (ft_putstr_fd("Invalid PID\n", 2), 1);
			i++;
		}
		if (!(argv[2][0]))
			return (ft_putstr_fd("No message provided, try again\n", 2), 1);
		sig_act.sa_handler = &sig_confirm;
		sig_act.sa_flags = 0;
		sigaction(SIGUSR1, &sig_act, NULL);
		send_bit(ft_atoi(argv[1]), argv[2]);
	}
	else
		ft_putstr_fd("Correct usage: ./client <SERVER_PID> <STRING>\n", 2);
	return (0);
}

static void	send_bit(int pid, char *str)
{
	int	i;
	int	c;

	i = 0;
	while (*str)
	{
		c = *str;
		while (i < 8)
		{
			if (c << i & 0b10000000)
			{
				if (kill(pid, SIGUSR1) == -1)
					ft_putstr_fd("Client: SIGUSR1 fail\n", 2);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					ft_putstr_fd("Client: SIGUSR2 fail\n", 2);
			}
			i++;
			usleep(150);
		}
		str++;
		i = 0;
	}
}

static void	sig_confirm(int sig)
{
	static int	msg_received = 0;

	if (!msg_received)
	{
		if (sig == SIGUSR1)
		{
			ft_putstr_fd("Signal sent successfully.\n", 1);
			msg_received = 1;
		}
	}
}
