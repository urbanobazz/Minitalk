/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:42:42 by ubazzane          #+#    #+#             */
/*   Updated: 2024/01/22 15:16:18 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_bit(int pid, char *str);

int	main(int argc, char **argv)
{
	int	i;

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
					ft_putstr_fd("Unable to send SIGUSR1\n", 2);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					ft_putstr_fd("Unable to send SIGUSR2\n", 2);
			}
			i++;
			usleep(150);
		}
		str++;
		i = 0;
	}
}
