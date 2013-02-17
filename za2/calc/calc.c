#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <glib.h>
#include "plugin.h"

//pointer to function, which return a double, and get 2 double as input
double (*pfunc)(double a, double b);
void *flib;
//dynamic link library error
const char *dlError;

extern int load_plugins(char *config, GSList **list);

int calc_test(double a, double b){
    GSList *list = NULL, *it = NULL;
    Plugin *pl = NULL;
    
    //insert a null node into list at first
    list = g_slist_append(list, NULL);
    
    char *phome = getenv("RPHOME");
    int code = 0;
    double result;

    if(phome == NULL){
        fprintf(stderr, "RPHOME is not set\n");
        return -1;
    }

    //load plugin defined in plugin.xml into list
    load_plugins("plugin.xml", &list);
    
    for(it = list; it != NULL; it = it->next){
        pl = (Plugin *)it->data;
        if(pl == NULL){
            continue;
        }else{
            //open the library
            flib = dlopen(pl->path, RTLD_LAZY);
            dlError = dlerror();

            if(dlError){
                fprintf(stderr, "open %s failed\n", pl->name);
                g_slist_free(list);
                return -1;
            }
            
            //get the entry
            *(void **)(&pfunc) = dlsym(flib, pl->entry);
            dlError = dlerror();
            if(dlError){
                fprintf(stderr, "find symbol %s failed\n", pl->entry);
                g_slist_free(list);
                return -1;
            }

            //call the function
            result = (*pfunc)(a, b);
            printf("%s(%f, %f) = %f\n", pl->entry, a, b, result);
            
            //then close it
            code = dlclose(flib);
            dlError = dlerror();

            if(code){
                fprintf(stderr, "close lib error\n");
                g_slist_free(list);
                return -1;
            }
        }
    }
    
    g_slist_free(list);
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 3){
        fprintf(stderr, "please input 2 numbers\n");
        return -1;
    }
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    calc_test(a, b);
    return 0;
}
