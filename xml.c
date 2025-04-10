#include "xml.h"

#include <stdlib.h>

int
xml_document_free (const XmlDocument *document)
{
  free (document->root);

  return 0;
}

int
xml_document_init (XmlDocument *document)
{
  if ((document->root = malloc (sizeof (*document->root))) == NULL)
    {
      return -1;
    }

  return 0;
}
