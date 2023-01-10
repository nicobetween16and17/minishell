/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:19:05 by gbierny           #+#    #+#             */
/*   Updated: 2023/01/10 22:19:07 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void env_in_alphabetic_order(char **envp)
{
    int i;
    int j;

    i = 0;
    char *front_arg;
    char *current_arg;
    while(envp[i])
    {
        j = i;
        while (envp[j + 1])
        {
            if(ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
            envp = switch_env_var(envp, i, j);
            j++;
        }
        i++;
    }
}

char **switch_env_var(char **envp, int i, int j)
{
    char *tmp;

    tmp = envp[i];

    envp[i] = malloc(sizeof(char) * (ft_strlen(envp[j] + 1)));
    if (!envp[i])
    {
       printf("malloc probleme");
        exit(0);
    }
    envp[i] = envp[j];
    envp[j] = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
    if (!envp[j])
    {
       printf("malloc error");
        exit(0);
    }
    envp[j] = tmp;
    return(envp);
}
