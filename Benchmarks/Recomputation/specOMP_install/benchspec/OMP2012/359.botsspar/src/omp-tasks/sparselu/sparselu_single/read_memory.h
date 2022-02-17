#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DOUBLE "double"
#define INT "int"

#define MAX_FILE_PATH 128

void* addr[128];
int count_addr = 0;
int ppid=0;


void ReadVarriable(void* array_addr[], int num)
{
    printf("num = %d\n",num);
    char pmem_name[MAX_FILE_PATH] = "/home/cc/nvc/tests/crush_mem.out.";
    char pcache_name[MAX_FILE_PATH] = "/home/cc/nvc/tests/crush_cache.out.";
    char pconsistentvaribles_name[MAX_FILE_PATH] = "/home/cc/nvc/tests/consistent_variable.out.";
    gethostname(pmem_name + strlen(pmem_name), MAX_FILE_PATH - strlen(pmem_name));
    gethostname(pcache_name + strlen(pcache_name), MAX_FILE_PATH - strlen(pcache_name));
    gethostname(pconsistentvaribles_name + strlen(pconsistentvaribles_name), MAX_FILE_PATH - strlen(pconsistentvaribles_name));
    sprintf(pmem_name + strlen(pmem_name), "%d", ppid);
    sprintf(pcache_name + strlen(pcache_name), "%d", ppid);
    sprintf(pconsistentvaribles_name + strlen(pconsistentvaribles_name), "%d", ppid);

    printf("%s\n",pmem_name);
    printf("%s\n",pcache_name);
    printf("%s\n",pconsistentvaribles_name);

    FILE *pinfo = fopen("/home/cc/nvc/tests/malloctrace.out", "r+");
    //FILE *pinfo = fopen("../../../tests/NPB3.0-omp-C/test.txt", "r+");
    FILE *pmem = fopen(pmem_name, "r+");
    FILE *pcache = fopen(pcache_name, "r+");
    FILE *pconsistentvaribles = fopen(pconsistentvaribles_name,"r+");
    FILE *pcheckpoint = fopen("/home/cc/specOMP_install/config/checkpoint","r+");
    char type[8];  //read the type
    char addr[64];
    int size;
    if(pinfo == NULL)
    {
      printf("malloctrace can not open!\n");
    }
    if(pmem == NULL)
    {
      printf("crush_mem can not open!\n");
    }
    if(pcache == NULL)
    {
      printf("crush_cache can not open!\n");
    }
    if(pconsistentvaribles == NULL)
    {
      printf("pconsistentvaribles can not open!\n");
    }
    if(pcheckpoint == NULL)
    {
        printf("checkpoint Files can not be opened!\n");
        return;
    }
    int i,it;

    for(it = 0; it<num; it++)
    {
        if(fscanf(pinfo,"%s %lu %s\n", addr, &size, type)==EOF)
        {
            printf("can't read iteration %d\n",it);
        }
        printf("it = %d : %s %ld %s\n",it, addr, size, type);
           if(size > 1)
           {
            if(strcmp(type,DOUBLE) == 0)
            {
                float *addr_base_double = (float*)array_addr[it];
                float temp_double;
                for(i = 0; i < size; i++)
                {
                    fscanf(pmem,"%f\n", &temp_double);
                    *(addr_base_double + i) = temp_double;
                }
		          /*  if(it==1){
                       printf("read from checkpoint\n");
			                 FILE *pcheckpoint = fopen("/home/cc/NPB3.3-OMP-C/checkpoint.txt","r+");
                       if(pcheckpoint == NULL)
                          printf("checkpoint file couldn't open\n");
                        for(i = 0; i < size; i++)
                        {
                            fscanf(pcheckpoint,"%lf\n", &temp_double);
                            *(addr_base_double + i) = temp_double;
                        }
                        fclose(pcheckpoint);
		              }*/
            }
            else if(strcmp(type,INT) == 0)
            {
                int *addr_base_int = (int*)array_addr[it];
                //printf("%p\n", addr_base_int);
                int temp_int;
                for(i = 0; i < size; i++)
                {
                  fscanf(pmem,"%d\n", &temp_int);
                  *(addr_base_int + i) = temp_int;
                }
            }

         }

        else{ //The variable need to be consistent
          //get the value derectly, don't pass the pointer's address, pass the variable's addr !
          if(strcmp(type,DOUBLE) == 0)
          {
              double *addr_base_double = (double*)array_addr[it];
              double temp_double;
                fscanf(pconsistentvaribles,"%lf\n", &temp_double);
                *(addr_base_double) = temp_double;
          }
          else if(strcmp(type,INT) == 0)
          {
              int *addr_base_int = (int*)array_addr[it];
              int temp_int;
              fscanf(pconsistentvaribles,"%d\n", &temp_int);
              *(addr_base_int) = temp_int;
          }
        }
    }
    fclose(pinfo);
    fclose(pmem);
    fclose(pcache);
    fclose(pconsistentvaribles);
    fclose(pcheckpoint);
}

/*
int main()
{
    void* addr[124];
    int num = 0;
    int colidx[NZ+1];
    addr[num++] = &colidx;
    //printf("%p\n",addr[0]);
    int rowstr[NA+1+1];
    addr[num++] = &rowstr;
    double a[NZ+1];
    addr[num++] = &a;
    double x[NA+2+1];
    addr[num++] = &x;
    double z[NA+2+1];
    addr[num++] = &z;
    double p[NA+2+1];
    addr[num++] = &p;
    double q[NA+2+1];
    addr[num++] = &q;
    double r[NA+2+1];
    addr[num++] = &r;
    int it;
    addr[num++] = &it;
    //static double w[NA+2+1];
    ReadVarriable(addr, num);
    int i;
    //for(i = 0; i< NZ+1; i++)
    //  printf("%d : %d\n",i,colidx[i]);

    //(i = 0; i< NA+2+1; i++)
    //  printf("%d : %lf\n",i,q[i]);

    return 0;
}
*/
