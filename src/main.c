/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:15:38 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/30 14:58:46 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_args			args;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments !");
		return (1);
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1)
		return (1);
	if (initialize(&args, argv, argc) == 0)
		return (1);
	if (args.nb_philo == 1)
	{
		print_state(&args, 1, "take a fork");
		sleep_mode(&args, args.t_die);
		print_state(&args, 1, "died");
		args.died = 1;
	}
	else
		executor(&args);
	return (0);
}
