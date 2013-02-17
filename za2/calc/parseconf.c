#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <glib.h>
#include "plugin.h"

const char* rootElement = "plugins";

//load plugins into a gslist, plugins information are defined in file config
int load_plugins(char *config, GSList **list);

xmlXPathObjectPtr get_plugin_nodes(xmlDocPtr doc, xmlChar *xpath);

int install_plugins(xmlNodeSetPtr nodes, GSList **list);

/**
 * just a helper, used to check what's inside of a list
 */
void print_list(GSList *list){
    GSList *it = NULL;
    Plugin *pl = NULL;

    for(it = list; it != NULL; it = it->next){
        pl = (Plugin *)it->data;
        printf("name = %s\n", pl->name);
        printf("path = %s\n", pl->path);
        printf("entry = %s\n", pl->entry);
        printf("version = %d\n", pl->version);
    }
}

int load_plugins(char *config, GSList **list){
    xmlDocPtr doc = NULL;
    xmlNodePtr current = NULL;
    xmlChar *key;

    doc = xmlReadFile(config, "UTF-8", 256);
    if(doc == NULL){
        fprintf(stderr, "load failed\n");
        return -1;
    }

    current = xmlDocGetRootElement(doc);
    if(current == NULL){
        fprintf(stderr, "get root failed\n");
        xmlFreeDoc(doc);
        return -1;
    }

    if(xmlStrcmp(current->name, (const xmlChar *)rootElement)){
        fprintf(stderr, "wrong format of input file");
        xmlFreeDoc(doc);
        return -1;
    }

    xmlXPathObjectPtr p = get_plugin_nodes(doc, (xmlChar *)"//plugin");
    if(p == NULL){
        fprintf(stderr, "error while get plugins");
        return -1;
    }

    if(*list == NULL){
        fprintf(stderr, "list is null\n");
        return -1;
    }
    install_plugins(p->nodesetval, list);

    return g_slist_length(*list);
}

/**
 * use xpath to get all nodes, which defined in doc(file config actually)
 */
xmlXPathObjectPtr get_plugin_nodes(xmlDocPtr doc, xmlChar *xpath){
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    context = xmlXPathNewContext(doc);
    if(context == NULL){
        fprintf(stderr, "error while new context\n");
        return NULL;
    }

    result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);

    if(result == NULL){
        fprintf(stderr, "error while evaluate expression\n");
        return NULL;
    }

    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        xmlXPathFreeObject(result);
        fprintf(stderr, "node set empty\n");
        return NULL;
    }

    return result;
}

/**
 * parse the nodes, and then put all nodes(struct Plugin) into list
 */
int install_plugins(xmlNodeSetPtr nodes, GSList **list){
    int i, size;
    size = (nodes) ? nodes->nodeNr : 0;
    xmlNodePtr current, config;

    Plugin *p = NULL;
    for(i = 0; i < size; i++){
        //new a Plugin
        p = (Plugin *)malloc(sizeof(Plugin));

        current = nodes->nodeTab[i];
        if(xmlHasProp(current, (const xmlChar*)"name")){
            xmlChar *attr = xmlGetProp(current, (const xmlChar*)"name");
            strcpy(p->name, attr);
        }
        config = current->xmlChildrenNode;
        xmlChar *temp = NULL;

        while(config != NULL){
            if(xmlStrcmp(config->name, (const xmlChar *)"library") == 0 
                    && xmlHasProp(config, (const xmlChar*)"path")){
                temp = xmlGetProp(config, (const xmlChar*)"path");
                strcpy(p->path, temp);
                temp = NULL;
            }else if(xmlStrcmp(config->name, (const xmlChar *)"entry") == 0
                    && xmlHasProp(config, (const xmlChar *)"name")){
                temp = xmlGetProp(config, (const xmlChar *)"name");
                strcpy(p->entry, temp);
                temp = NULL;
            }else{
                printf("wrong configuration structure\n");
            }
            config = config->next;
        }
        //insert into list
        *list = g_slist_append(*list, p);
    }

    return 0;
}


//for unit testing
/*
int main(int argc, char **argv){
    GSList *list = NULL;

    list = g_slist_append(list, NULL);

    load_plugins("plugin.xml", &list);

    print_list(list);

    g_slist_free(list);

    return 0;
}
*/
