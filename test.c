#include <stdio.h>
#include <utmp.h>

int main()
{
    for(struct utmp* user = getutent(); user; user = getutent())  
    {
        printf("ma cacai\n");
        printf("%s\n", user->ut_user);
        printf("%s\n", user->ut_host);
        printf("%d\n", user->ut_tv.tv_sec);
        //printf("%u\n", user->ut_tv.tv_usec);
    }

    return 0;
}
