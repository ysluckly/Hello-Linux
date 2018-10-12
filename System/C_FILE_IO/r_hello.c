#include <unistd.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("myfile",'r');
    if(!fp)
    {
        printf("file to read\n");
    }

    char buf[1024];
    const char *p = "hello linux\n";
    while(1)
    {
        size_t s= fread(buf,1,strlen(p),fp);
        if(s>0)
        {
            buf[s] = 0;
            printf("%s",buf);
        }
        
        if(feof(fp))
        {
            break;
        }
    }
    
    fclose(fp);
    return 0;


}
