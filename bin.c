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

char *bool_to_string (bool b);

double bytes_to_double (const unsigned char *bytes);

char *bytes_to_hex (const unsigned char *bytes, size_t size);

unsigned char *double_to_bytes (double d);

unsigned char *hex_to_bytes (const char *hex, size_t size);

char *number_to_string (const char *format, const void *number);

char *string_remove_whitespace (const char *string);

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
