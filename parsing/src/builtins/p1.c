# include "../../include/header.h"

int export_v(t_env *env, char *key, char *value)
{
    if (!env || !key || !value)
        return (1);
    add_env(env, key, value);
    return (0);
}

t_env *unset_v(t_env *env, char *key)
{
    if (!env || !key)
        return (NULL);
    return (delone_env(env, key));
}

void put_env(t_env *env)
{
    if (!env)
    {
        write(1, "\n", 1);
        return;
    }
    while (env != NULL)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}
void ft_echo(char **argv)
{
    int i;
    int temp;

    temp = 1;
    i = 1;
    while (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
        i++;
    if (i == 1)
        temp = 0;
    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        if (temp)
            write(1, "\n", 1);
        i++;
    }
}
