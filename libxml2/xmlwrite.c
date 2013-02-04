#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char **argv)
{
        xmlDocPtr doc = NULL;
        xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;

        doc = xmlNewDoc(BAD_CAST "1.0"); // create a new xml document.
        root_node = xmlNewNode(NULL, BAD_CAST "root"); // create a root node.
        xmlDocSetRootElement(doc, root_node);

        xmlNewChild(root_node, NULL, BAD_CAST "node1", BAD_CAST "content of node1");
        //xmlNewChild(root_node, NULL, BAD_CAST "node2", NULL);

        node = xmlNewChild(root_node, NULL, BAD_CAST "node3", BAD_CAST "node3 has attributes");
        xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");

        node = xmlNewNode(NULL, BAD_CAST "node4");
        node1 = xmlNewText(BAD_CAST
                   "other way to create content (which is also a node)");
        xmlAddChild(node, node1);
        xmlAddChild(root_node, node);

        xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1);

        xmlFreeDoc(doc);

        xmlCleanupParser();

        xmlMemoryDump();
        return(0);
}
