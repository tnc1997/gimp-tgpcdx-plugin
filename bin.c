#include "bin.h"

#include <stdlib.h>
#include <string.h>

double bytes_to_double (const unsigned char *bytes);

unsigned char *double_to_bytes (double d);

char *int_to_string (int i);

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

char *
int_to_string (const int i)
{
  const size_t size = snprintf (NULL, 0, "%d", i) + 1;

  char *string;

  if ((string = malloc (size)) == NULL)
    {
      return NULL;
    }

  snprintf (string, size, "%d", i);

  return string;
}
