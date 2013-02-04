#include "getConfig.h" 

int getConfig(char *xmlFilename, xmlStruct *xmlStructname)
{
  xmlDocPtr doc;
  xmlNodePtr curNode;

  xmlKeepBlanksDefault(0);
  doc = xmlReadFile(xmlFilename, "UTF-8", XML_PARSE_RECOVER); // open a xml doc.
  curNode = xmlDocGetRootElement(doc);

  if (curNode == NULL) {
    fprintf(stderr, "open file failed. \n");
    xmlFreeDoc (doc);
    return -1;
  }

  // if the same,xmlStrcmp return 0, else return 1
  if (xmlStrcmp(curNode->name, "config")) {
    fprintf(stderr, "check configElement failed. \n");
    xmlFreeDoc (doc);
    return -1;
  }

  curNode = curNode->children; // move to config element's children.
  char *nodeName;
  char *content;
  while (curNode != NULL) {
    nodeName = (char *)curNode -> name; 
    content = (char *) xmlNodeGetContent(curNode);
    printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content);
    sprintf(xmlStructname -> localip, "%s", content);
    curNode = curNode->next;
  }

  //if (curNode != NULL)
  //{
  //  nodeName = (char *) curNode->name; 
  //  content = (char *) xmlNodeGetContent(curNode);
  //  printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content);
  //  sprintf(xmlStructname -> localip, "%s", content);
  //}

  //curNode = curNode->next;
  //if (curNode != NULL)
  //{
  //  nodeName = (char *) curNode->name;
  //  content = (char *) xmlNodeGetContent(curNode);
  //  printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content); 
  //  sprintf(xmlStructname -> localport, "%s", content);
  //}

  //curNode = curNode->next;
  //if (curNode != NULL)
  //{
  //  nodeName = (char *) curNode->name;
  //  content = (char *) xmlNodeGetContent(curNode);
  //  printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content);   
  //  sprintf(xmlStructname -> remoteip, "%s", content);
  //}

  //curNode = curNode->next;
  //if (curNode != NULL)
  //{
  //  nodeName = (char *) curNode->name;
  //  content = (char *) xmlNodeGetContent(curNode);
  //  printf ("Current node name:%s,\t the content is:%s.\n\n", nodeName, content);   
  //  sprintf(xmlStructname -> remoteport, "%s", content);
  //}

  xmlFree(curNode);
  xmlFreeDoc(doc);
  return 0;
}

int main(int argc, char **argv)
{
  xmlStruct sb;
  getConfig("./config/platsend.xml", &sb);
  printf("sb:%s\n", sb.localip);
  printf("sb:%s\n", sb.localport);
  printf("sb:%s\n", sb.remoteip);
  printf("sb:%s\n", sb.remoteport);
  return 0;
}
