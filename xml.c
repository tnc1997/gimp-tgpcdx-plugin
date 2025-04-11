#include "xml.h"

#include <stdlib.h>

int
xml_attribute_free (const XmlAttribute *attribute)
{
  free (attribute->name);
  free (attribute->value);

  return 0;
}

int
xml_attribute_init (XmlAttribute *attribute)
{
  if ((attribute->name = malloc (sizeof (*attribute->name))) == NULL)
    {
      return -1;
    }

  if ((attribute->value = malloc (sizeof (*attribute->value))) == NULL)
    {
      return -1;
    }

  return 0;
}

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
