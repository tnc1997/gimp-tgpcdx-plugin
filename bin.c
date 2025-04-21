#include "bin.h"

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
