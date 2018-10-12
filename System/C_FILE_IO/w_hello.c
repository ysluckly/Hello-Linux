#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("myfile",'w');
    if(!fp)
    {
        printf("file to open");
    }

    const char *p = "hello linux\n";
    int i = 5;
    while(i--)
    {
        fwrite(p, strlen(p), 1, fp);
    }

    fclose(fp);
    return 0;

}

