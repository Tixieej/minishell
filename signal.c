/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/26 13:24:06 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

// Control c = SIGINT (2), bash blijft runnen maar process binnen bash stopt.
// Control d = waarde uitzoeken!, processen stoppen(control c aanroepen?) en bash stopt.  

void sig_handler(int signo)
{
  if (signo == SIGINT)
    exit(0);
}

int main(void)
{
  if (signal(SIGINT, sig_handler) == SIG_ERR)
    printf("\ncan't catch SIGINT\n");
  while(1) 
    sleep(1);
  return 0;
}




