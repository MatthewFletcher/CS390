#include <stdio.h>
#include <unistd.h>
int main()
{
    char* arr[] = {"myls","-a", NULL};
    execv(arr[0], arr);
    return 0;
}
