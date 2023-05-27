#include "header.h"

/**
 * main - Entry point
 * @argcount: Argument count
 * @argvector: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argcount, char **argvector)
{
    info_t info[] = { INFO_INIT };
    int ford = 2;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (ford)
        : "r" (ford));

    if (argcount == 2)
    {
        ford = open(argvector[1], O_RDONLY);
        if (ford == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(argvector[0]);
                _eputs(": 0: Can't open ");
                _eputs(argvector[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = ford;
    }

    populate_env_list(info);
    recount_history(info);
    hsh(info, argvector);

    return (EXIT_SUCCESS);
}
