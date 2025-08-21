#include "bin.h"

#include <stdlib.h>
#include <string.h>

#define XML_NS_HREF   "http://www.kuju.com/TnT/2003/Delta"
#define XML_NS_PREFIX "d"

#define XML_NEW_NS xmlNewNs (NULL, XML_NS_HREF, XML_NS_PREFIX)

typedef struct BinBlobElement
{
  size_t         size;
  unsigned char *bytes;
} BinBlobElement;

typedef struct BinClosingElement
{
  char *name;
} BinClosingElement;

typedef struct BinMatrixElement
{
  char             *name;
  RailWorksDataType element_type;
  size_t            num_elements;
  void            **elements;
} BinMatrixElement;

typedef struct BinNullElement
{
} BinNullElement;

typedef struct BinOpeningElement
{
  char             *name;
  unsigned long int id;
  size_t            num_children;
} BinOpeningElement;

typedef struct BinReferenceElement
{
  char             *name;
  unsigned long int id;
} BinReferenceElement;

typedef struct BinValueElement
{
  char             *name;
  RailWorksDataType type;
  void             *value;
} BinValueElement;

typedef union BinElementData
{
  BinBlobElement      *blob;
  BinClosingElement   *closing;
  BinMatrixElement    *matrix;
  BinNullElement      *null;
  BinOpeningElement   *opening;
  BinReferenceElement *reference;
  BinValueElement     *value;
} BinElementData;

struct BinElement
{
  BinElementData data;
  BinElementType type;
};

xmlNode *bin_blob_element_to_xml_node (const BinBlobElement *element);

xmlNode *bin_closing_element_to_xml_node (const BinClosingElement *element);

xmlNode *bin_matrix_element_to_xml_node (const BinMatrixElement *element);

xmlNode *bin_null_element_to_xml_node (const BinNullElement *element);

xmlNode *bin_opening_element_to_xml_node (const BinOpeningElement *element);

xmlNode *bin_reference_element_to_xml_node (const BinReferenceElement *element);

xmlNode *bin_value_element_to_xml_node (const BinValueElement *element);

char *bool_to_string (bool b);

double bytes_to_double (const unsigned char *bytes);

char *bytes_to_hex (const unsigned char *bytes, size_t size);

unsigned char *double_to_bytes (double d);

unsigned char *hex_to_bytes (const char *hex, size_t size);

char *number_to_string (const char *format, const void *number);

char *string_remove_whitespace (const char *string);

BinBlobElement *xml_node_to_bin_blob_element (const xmlNode *node);

BinMatrixElement *xml_node_to_bin_matrix_element (const xmlNode *node);

BinNullElement *xml_node_to_bin_null_element (const xmlNode *node);

BinReferenceElement *xml_node_to_bin_reference_element (const xmlNode *node);

BinValueElement *xml_node_to_bin_value_element (const xmlNode *node);

xmlNode *
bin_element_to_xml_node (const BinElement *element)
{
  switch (element->type)
    {
    case BIN_ELEMENT_TYPE_MATRIX:
      return bin_matrix_element_to_xml_node (element->data.matrix);
    case BIN_ELEMENT_TYPE_BLOB:
      return bin_blob_element_to_xml_node (element->data.blob);
    case BIN_ELEMENT_TYPE_NULL:
      return bin_null_element_to_xml_node (element->data.null);
    case BIN_ELEMENT_TYPE_OPENING:
      return bin_opening_element_to_xml_node (element->data.opening);
    case BIN_ELEMENT_TYPE_REFERENCE:
      return bin_reference_element_to_xml_node (element->data.reference);
    case BIN_ELEMENT_TYPE_VALUE:
      return bin_value_element_to_xml_node (element->data.value);
    case BIN_ELEMENT_TYPE_CLOSING:
      return bin_closing_element_to_xml_node (element->data.closing);
    default:
      return NULL;
    }
}

char *
railworks_data_type_to_string (const RailWorksDataType type)
{
  switch (type)
    {
    case RAILWORKS_DATA_TYPE_BOOL:
      return "bool";
    case RAILWORKS_DATA_TYPE_C_DELTA_STRING:
      return "cDeltaString";
    case RAILWORKS_DATA_TYPE_S_FLOAT32:
      return "sFloat32";
    case RAILWORKS_DATA_TYPE_S_INT8:
      return "sInt8";
    case RAILWORKS_DATA_TYPE_S_INT16:
      return "sInt16";
    case RAILWORKS_DATA_TYPE_S_INT32:
      return "sInt32";
    case RAILWORKS_DATA_TYPE_S_INT64:
      return "sInt64";
    case RAILWORKS_DATA_TYPE_S_U_INT8:
      return "sUInt8";
    case RAILWORKS_DATA_TYPE_S_U_INT16:
      return "sUInt16";
    case RAILWORKS_DATA_TYPE_S_U_INT32:
      return "sUInt32";
    case RAILWORKS_DATA_TYPE_S_U_INT64:
      return "sUInt64";
    default:
      return NULL;
    }
}

RailWorksDataType
string_to_railworks_data_type (const char *string)
{
  if (strcmp (string, "bool") == 0)
    {
      return RAILWORKS_DATA_TYPE_BOOL;
    }

  if (strcmp (string, "cDeltaString") == 0)
    {
      return RAILWORKS_DATA_TYPE_C_DELTA_STRING;
    }

  if (strcmp (string, "sFloat32") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_FLOAT32;
    }

  if (strcmp (string, "sInt8") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_INT8;
    }

  if (strcmp (string, "sInt16") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_INT16;
    }

  if (strcmp (string, "sInt32") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_INT32;
    }

  if (strcmp (string, "sInt64") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_INT64;
    }

  if (strcmp (string, "sUInt8") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_U_INT8;
    }

  if (strcmp (string, "sUInt16") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_U_INT16;
    }

  if (strcmp (string, "sUInt32") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_U_INT32;
    }

  if (strcmp (string, "sUInt64") == 0)
    {
      return RAILWORKS_DATA_TYPE_S_U_INT64;
    }

  return -1;
}

BinElement *
xml_node_to_bin_element (const xmlNode *node)
{
  const char *element_type = (char *) xmlGetNsProp (node, "elementType", XML_NS_HREF);
  const char *num_elements = (char *) xmlGetNsProp (node, "numElements", XML_NS_HREF);
  const char *size         = (char *) xmlGetNsProp (node, "size", XML_NS_HREF);
  const char *type         = (char *) xmlGetNsProp (node, "type", XML_NS_HREF);

  BinElement *element;

  if ((element = malloc (sizeof (BinElement))) == NULL)
    {
      return NULL;
    }

  if (strcmp ((char *) node->name, "blob") == 0 && size != NULL)
    {
      element->type = BIN_ELEMENT_TYPE_BLOB;

      if ((element->data.blob = xml_node_to_bin_blob_element (node)) == NULL)
        {
          free (element);

          return NULL;
        }

      return element;
    }

  if (element_type != NULL && num_elements != NULL)
    {
      element->type = BIN_ELEMENT_TYPE_MATRIX;

      if ((element->data.matrix = xml_node_to_bin_matrix_element (node)) == NULL)
        {
          free (element);

          return NULL;
        }

      return element;
    }

  if (strcmp ((char *) node->name, "nil") == 0)
    {
      element->type = BIN_ELEMENT_TYPE_NULL;

      if ((element->data.null = xml_node_to_bin_null_element (node)) == NULL)
        {
          free (element);

          return NULL;
        }

      return element;
    }

  if (strcmp (type, "ref") == 0)
    {
      element->type = BIN_ELEMENT_TYPE_REFERENCE;

      if ((element->data.reference = xml_node_to_bin_reference_element (node)) == NULL)
        {
          free (element);

          return NULL;
        }

      return element;
    }

  if (type != NULL)
    {
      element->type = BIN_ELEMENT_TYPE_VALUE;

      if ((element->data.value = xml_node_to_bin_value_element (node)) == NULL)
        {
          free (element);

          return NULL;
        }

      return element;
    }

  free (element);

  return NULL;
}

xmlNode *
bin_blob_element_to_xml_node (const BinBlobElement *element)
{
  xmlNode *node = xmlNewNode (XML_NEW_NS, "blob");

  const char *size = number_to_string ("%lu", &element->size);
  xmlNewNsProp (node, XML_NEW_NS, "size", (xmlChar *) size);

  const char *content = bytes_to_hex (element->bytes, element->size);
  xmlNodeSetContent (node, (xmlChar *) content);

  return node;
}

xmlNode *
bin_closing_element_to_xml_node (const BinClosingElement *element)
{
  return xmlNewNode (NULL, (xmlChar *) element->name);
}

xmlNode *
bin_matrix_element_to_xml_node (const BinMatrixElement *element)
{
  xmlNode *node = xmlNewNode (NULL, (xmlChar *) element->name);

  const char *num_elements = number_to_string ("%lu", &element->num_elements);
  xmlNewNsProp (node, XML_NEW_NS, "numElements", (xmlChar *) num_elements);

  const char *element_type = railworks_data_type_to_string (element->element_type);
  xmlNewNsProp (node, XML_NEW_NS, "elementType", (xmlChar *) element_type);

  if (element->element_type == RAILWORKS_DATA_TYPE_S_FLOAT32)
    {
      const char *precision = "string";
      xmlNewNsProp (node, XML_NEW_NS, "precision", (xmlChar *) precision);
    }

  char **elements;

  if ((elements = malloc (element->num_elements * sizeof (*elements))) == NULL)
    {
      free (node);

      return NULL;
    }

  for (int i = 0; i < element->num_elements; i++)
    {
      switch (element->element_type)
        {
        case RAILWORKS_DATA_TYPE_BOOL:
          {
            if ((elements[i] = bool_to_string (*(bool *) &element->elements[i])) == NULL)
              {
                free (elements);
                free (node);

                return NULL;
              }

            break;
          }
        case RAILWORKS_DATA_TYPE_C_DELTA_STRING:
          {
            if ((elements[i] = malloc (strlen (element->elements[i]) + 1)) == NULL)
              {
                free (elements);
                free (node);

                return NULL;
              }

            if (strcpy (elements[i], element->elements[i]) == NULL)
              {
                free (elements);
                free (node);

                return NULL;
              }

            break;
          }
        case RAILWORKS_DATA_TYPE_S_FLOAT32:
          {
            if ((elements[i] = number_to_string ("%.7f", element->elements[i])) == NULL)
              {
                free (elements);
                free (node);

                return NULL;
              }

            break;
          }
        case RAILWORKS_DATA_TYPE_S_INT8:
        case RAILWORKS_DATA_TYPE_S_INT16:
        case RAILWORKS_DATA_TYPE_S_INT32:
        case RAILWORKS_DATA_TYPE_S_INT64:
        case RAILWORKS_DATA_TYPE_S_U_INT8:
        case RAILWORKS_DATA_TYPE_S_U_INT16:
        case RAILWORKS_DATA_TYPE_S_U_INT32:
        case RAILWORKS_DATA_TYPE_S_U_INT64:
          {
            if ((elements[i] = number_to_string ("%ld", element->elements[i])) == NULL)
              {
                free (elements);
                free (node);

                return NULL;
              }

            break;
          }
        default:
          {
            free (elements);
            free (node);

            return NULL;
          }
        }
    }

  size_t size = 0;

  for (int i = 0; i < element->num_elements; i++)
    {
      size += strlen (elements[i]) + 1;
    }

  char *content;

  if ((content = malloc (size)) == NULL)
    {
      free (elements);
      free (node);

      return NULL;
    }

  for (int i = 0; i < element->num_elements; i++)
    {
      if (sprintf (content + i * (size + 1), "%s", elements[i]) == 0)
        {
          free (content);
          free (elements);
          free (node);

          return NULL;
        }

      if (sprintf (content + i * (size + 1) + strlen (elements[i]) + 1, "%c", ' ') == 0)
        {
          free (content);
          free (elements);
          free (node);

          return NULL;
        }
    }

  xmlNodeSetContent (node, (xmlChar *) content);

  free (content);
  free (elements);

  return node;
}

xmlNode *
bin_null_element_to_xml_node (const BinNullElement *element)
{
  return xmlNewNode (XML_NEW_NS, "nil");
}

xmlNode *
bin_opening_element_to_xml_node (const BinOpeningElement *element)
{
  xmlNode *node = xmlNewNode (NULL, (xmlChar *) element->name);

  if (element->id != 0)
    {
      const char *id = number_to_string ("%lu", &element->id);
      xmlNewNsProp (node, XML_NEW_NS, "id", (xmlChar *) id);
    }

  return node;
}

xmlNode *
bin_reference_element_to_xml_node (const BinReferenceElement *element)
{
  xmlNode *node = xmlNewNode (NULL, (xmlChar *) element->name);

  xmlNewNsProp (node, XML_NEW_NS, "type", "ref");

  return node;
}

xmlNode *
bin_value_element_to_xml_node (const BinValueElement *element)
{
  xmlNode *node = xmlNewNode (NULL, (xmlChar *) element->name);

  const char *type = railworks_data_type_to_string (element->type);
  xmlNewNsProp (node, XML_NEW_NS, "type", (xmlChar *) type);

  if (element->type == RAILWORKS_DATA_TYPE_S_FLOAT32)
    {
      const double         value        = *(double *) &element->value;
      const unsigned char *bytes        = double_to_bytes (value);
      const char          *alt_encoding = bytes_to_hex (bytes, sizeof (value));
      xmlNewNsProp (node, XML_NEW_NS, "alt_encoding", (xmlChar *) alt_encoding);

      const char *precision = "string";
      xmlNewNsProp (node, XML_NEW_NS, "precision", (xmlChar *) precision);
    }

  return node;
}

char *
bool_to_string (const bool b)
{
  return b == true ? "1" : "0";
}

double
bytes_to_double (const unsigned char *bytes)
{
  double d;

  if (memcpy (&d, bytes, sizeof (d)) == NULL)
    {
      return -1;
    }

  return d;
}

char *
bytes_to_hex (const unsigned char *bytes, const size_t size)
{
  if (bytes == NULL)
    {
      return NULL;
    }

  char *hex;

  if ((hex = malloc (size * 2 + 1)) == NULL)
    {
      return NULL;
    }

  for (int i = 0; i < size; i++)
    {
      if (sprintf (hex + i * 2, "%02x", bytes[i]) == 0)
        {
          free (hex);

          return NULL;
        }
    }

  return hex;
}

unsigned char *
double_to_bytes (const double d)
{
  unsigned char *bytes;

  if ((bytes = malloc (sizeof (d))) == NULL)
    {
      return NULL;
    }

  if (memcpy (bytes, &d, sizeof (d)) == NULL)
    {
      return NULL;
    }

  return bytes;
}

unsigned char *
hex_to_bytes (const char *hex, const size_t size)
{
  if (hex == NULL)
    {
      return NULL;
    }

  unsigned char *bytes;

  if ((bytes = malloc (size / 2 + 1)) == NULL)
    {
      return NULL;
    }

  for (int i = 0; i < size / 2; i++)
    {
      char *dest = malloc (3);

      if (memcpy (dest, hex + i * 2, 2) == 0)
        {
          free (dest);

          return NULL;
        }

      char *end = NULL;

      bytes[i] = strtol (dest, &end, 16);

      if (end != dest + 2)
        {
          free (dest);

          return NULL;
        }

      free (dest);
    }

  return bytes;
}

char *
number_to_string (const char *format, const void *number)
{
  const size_t size = snprintf (NULL, 0, format, &number) + 1;

  char *string;

  if ((string = malloc (size)) == NULL)
    {
      return NULL;
    }

  if (snprintf (string, size, format, &number) == 0)
    {
      free (string);

      return NULL;
    }

  return string;
}

char *
string_remove_whitespace (const char *string)
{
  if (string == NULL)
    {
      return NULL;
    }

  char *result;

  if ((result = malloc (strlen (string) + 1)) == NULL)
    {
      return NULL;
    }

  int count = 0;

  for (int i = 0; i < strlen (string); i++)
    {
      if (string[i] != ' ')
        {
          result[count] = string[i];

          count++;
        }
    }

  result[count] = '\0';

  return result;
}

BinBlobElement *
xml_node_to_bin_blob_element (const xmlNode *node)
{
  BinBlobElement *element;

  if ((element = malloc (sizeof (*element))) == NULL)
    {
      return NULL;
    }

  const char *size;

  if ((size = (char *) xmlGetNsProp (node, "size", XML_NS_HREF)) == NULL)
    {
      free (element);

      return NULL;
    }

  element->size = strtoul (size, NULL, 10);

  const char *content;

  if ((content = (char *) xmlNodeGetContent (node)) == NULL)
    {
      free (element);

      return NULL;
    }

  const char *hex;

  if ((hex = string_remove_whitespace (content)) == NULL)
    {
      free (element);

      return NULL;
    }

  if ((element->bytes = hex_to_bytes (hex, strlen (hex))) == NULL)
    {
      free (element);

      return NULL;
    }

  return element;
}

BinMatrixElement *
xml_node_to_bin_matrix_element (const xmlNode *node)
{
  BinMatrixElement *element;

  if ((element = malloc (sizeof (*element))) == NULL)
    {
      return NULL;
    }

  if ((element->name = malloc (strlen ((char *) node->name) + 1)) == NULL)
    {
      free (element);

      return NULL;
    }

  if (strcpy (element->name, (char *) node->name) == NULL)
    {
      free (element);

      return NULL;
    }

  const char *element_type;

  if ((element_type = (char *) xmlGetNsProp (node, "elementType", XML_NS_HREF)) == NULL)
    {
      free (element);

      return NULL;
    }

  if ((element->element_type = string_to_railworks_data_type (element_type)) == -1)
    {
      free (element);

      return NULL;
    }

  const char *num_elements;

  if ((num_elements = (char *) xmlGetNsProp (node, "numElements", XML_NS_HREF)) == NULL)
    {
      free (element);

      return NULL;
    }

  element->num_elements = strtoul (num_elements, NULL, 10);

  if ((element->elements = malloc (element->num_elements * sizeof (*element->elements))) == NULL)
    {
      free (element);

      return NULL;
    }

  char *content;

  if ((content = (char *) xmlNodeGetContent (node)) == NULL)
    {
      free (element);

      return NULL;
    }

  const char *token = strtok (content, " ");

  for (int i = 0; i < element->num_elements; i++)
    {
      if (token == NULL)
        {
          free (element);

          return NULL;
        }

      switch (element->element_type)
        {
        case RAILWORKS_DATA_TYPE_BOOL:
          {
            int value = strcmp (token, "1") == 0;

            element->elements[i] = &value;

            break;
          }
        case RAILWORKS_DATA_TYPE_C_DELTA_STRING:
          {
            if ((element->elements[i] = malloc (strlen (token) + 1)) == NULL)
              {
                free (element);

                return NULL;
              }

            if (strcpy (element->elements[i], token) == NULL)
              {
                free (element);

                return NULL;
              }

            break;
          }
        case RAILWORKS_DATA_TYPE_S_FLOAT32:
          {
            double value = strtod (token, NULL);

            element->elements[i] = &value;

            break;
          }
        case RAILWORKS_DATA_TYPE_S_INT8:
        case RAILWORKS_DATA_TYPE_S_INT16:
        case RAILWORKS_DATA_TYPE_S_INT32:
        case RAILWORKS_DATA_TYPE_S_INT64:
        case RAILWORKS_DATA_TYPE_S_U_INT8:
        case RAILWORKS_DATA_TYPE_S_U_INT16:
        case RAILWORKS_DATA_TYPE_S_U_INT32:
        case RAILWORKS_DATA_TYPE_S_U_INT64:
          {
            unsigned long int value = strtoul (token, NULL, 10);

            element->elements[i] = &value;

            break;
          }
        default:
          {
            free (element);

            return NULL;
          }
        }

      token = strtok (NULL, " ");
    }

  return element;
}

BinNullElement *
xml_node_to_bin_null_element (const xmlNode *node)
{
  BinNullElement *element;

  if ((element = malloc (sizeof (*element))) == NULL)
    {
      return NULL;
    }

  return element;
}

BinReferenceElement *
xml_node_to_bin_reference_element (const xmlNode *node)
{
  BinReferenceElement *element;

  if ((element = malloc (sizeof (*element))) == NULL)
    {
      return NULL;
    }

  if ((element->name = malloc (strlen ((char *) node->name) + 1)) == NULL)
    {
      free (element);

      return NULL;
    }

  if (strcpy (element->name, (char *) node->name) == NULL)
    {
      free (element);

      return NULL;
    }

  const char *content;

  if ((content = (char *) xmlNodeGetContent (node)) == NULL)
    {
      free (element);

      return NULL;
    }

  element->id = strtoul (content, NULL, 10);

  return element;
}

BinValueElement *
xml_node_to_bin_value_element (const xmlNode *node)
{
  BinValueElement *element;

  if ((element = malloc (sizeof (*element))) == NULL)
    {
      return NULL;
    }

  if ((element->name = malloc (strlen ((char *) node->name) + 1)) == NULL)
    {
      free (element);

      return NULL;
    }

  if (strcpy (element->name, (char *) node->name) == NULL)
    {
      free (element);

      return NULL;
    }

  const char *type;

  if ((type = (char *) xmlGetNsProp (node, "type", XML_NS_HREF)) == NULL)
    {
      free (element);

      return NULL;
    }

  if ((element->type = string_to_railworks_data_type (type)) == -1)
    {
      free (element);

      return NULL;
    }

  const char *content;

  if ((content = (char *) xmlNodeGetContent (node)) == NULL)
    {
      free (element);

      return NULL;
    }

  switch (element->type)
    {
    case RAILWORKS_DATA_TYPE_BOOL:
      {
        int value = strcmp (content, "1") == 0;

        element->value = &value;

        break;
      }
    case RAILWORKS_DATA_TYPE_C_DELTA_STRING:
      {
        if ((element->value = malloc (strlen (content) + 1)) == NULL)
          {
            free (element);

            return NULL;
          }

        if (strcpy (element->value, content) == NULL)
          {
            free (element);

            return NULL;
          }

        break;
      }
    case RAILWORKS_DATA_TYPE_S_FLOAT32:
      {
        double value = strtod (content, NULL);

        element->value = &value;

        break;
      }
    case RAILWORKS_DATA_TYPE_S_INT8:
    case RAILWORKS_DATA_TYPE_S_INT16:
    case RAILWORKS_DATA_TYPE_S_INT32:
    case RAILWORKS_DATA_TYPE_S_INT64:
    case RAILWORKS_DATA_TYPE_S_U_INT8:
    case RAILWORKS_DATA_TYPE_S_U_INT16:
    case RAILWORKS_DATA_TYPE_S_U_INT32:
    case RAILWORKS_DATA_TYPE_S_U_INT64:
      {
        unsigned long int value = strtoul (content, NULL, 10);

        element->value = &value;

        break;
      }
    default:
      {
        free (element);

        return NULL;
      }
    }

  return element;
}
