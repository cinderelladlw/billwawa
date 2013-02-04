#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

int main(int argc, char **argv)
{
        xmlDocPtr doc;
        xmlNodePtr curNode;

        xmlKeepBlanksDefault(0);
        doc = xmlReadFile("mine.xml", "UTF-8", XML_PARSE_RECOVER); // open a xml doc.
        curNode = xmlDocGetRootElement(doc); // get root element.

        if (curNode == NULL)
        {
                fprintf(stderr, "open file failed. \n");
                xmlFreeDoc (doc);
                return -1;
        }

        if (xmlStrcmp(curNode->name, "root")) // if the same,xmlStrcmp return 0, else return 1
        {
                fprintf(stderr, "check rootElement failed. \n");
                xmlFreeDoc (doc);
                return -1;
        }

        curNode = curNode->children; // move to root element's children.
        char *nodeName;
        char *content;

        if (curNode != NULL)
        {
                nodeName = (char *) curNode->name; 
                content = (char *) xmlNodeGetContent(curNode);
                printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content);
        }

        curNode = curNode->next;
        char *attr;
        if (curNode != NULL)
        {
                nodeName = (char *) curNode->name;
                content = (char *) xmlNodeGetContent(curNode);
                attr = (char *) xmlGetProp(curNode, (const xmlChar *)"attribute"); // get node attribute
                printf ("Current node name:%s,\t the content is:%s,\t AND THE ATTR IS:%s.\n\n", nodeName, content,attr); 
        }

        curNode = curNode->next;
        if (curNode != NULL)
        {
                nodeName = (char *) curNode->name;
                content = (char *) xmlNodeGetContent(curNode);
                printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content);   
        }

        xmlFree(curNode);
        xmlFreeDoc(doc);
        return 1;
}
