/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:06:24 by acakste           #+#    #+#             */
/*   Updated: 2018/11/19 09:06:25 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <stdio.h>

int		main(void)
{
	char *key = "foo";
	char *value = "bar";

	store_local_var(key, value);
	value = "baz";
	store_local_var(key, value);
	// rm_local_var(key);
	printf("Result: %s\n", get_local_var(key));

	// char	arr[5] = {'\0'};
	// int	i;
	// int	j;
	// char *key2 = "ag";
	// unsigned long hash;

	// hash = hash_var(key2);
	// i = 0;
	// while (i < 25)
	// {
	// 	j = 0;
	// 	arr[0] = i + 'a';
	// 	while (j < 25)
	// 	{
	// 		arr[1] = j + 'a';
	// 		if (hash_var(arr) % 20 == hash % 20)
	// 		{
	// 			(void)j;
	// 			printf("%s\n", arr);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }

	// char	*keys[10] = {"ag", "bn", "ca", "cu", "dh", "eo", "fb", "fv", "gi", "hp"};
	// char	value[2] = {'\0'};

	// int k = 0;
	// while (k < 10)
	// {
	// 	value[0] = k + 48;
	// 	store_local_var(keys[k], value);
	// 	k++;
	// }

	// int k2 = 1;

	// while (k2 < 10)
	// {
	// 	k = 0;
	// 	while (k < 10)
	// 	{
	// 		printf("num: %d  %s\n", k, get_local_var(keys[k]));
	// 		k++;
	// 	}
	// 	rm_local_var(keys[k2]);
	// 	k2 += 2;
	// }
	return (0);
}