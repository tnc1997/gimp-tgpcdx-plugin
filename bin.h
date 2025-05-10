#ifndef BIN_H
#define BIN_H

typedef enum BinElementType {
  /**
   * ```xml
   * <name d:numElements="2" d:elementType="bool">0 1</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="cDeltaString">abc def</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sFloat32" d:precision="string">1.0000000 2.0000000</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sInt8">-128 127</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sInt16">-32768 32767</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sInt32">-2147483648 2147483647</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sInt64">-9223372036854775808 9223372036854775807</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sUInt8">0 255</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sUInt16">0 65535</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sUInt32">0 4294967295</name>
   * ```
   * ```xml
   * <name d:numElements="2" d:elementType="sUInt64">0 18446744073709551615</name>
   * ```
   */
  BIN_ELEMENT_TYPE_MATRIX    = 0x41,
  /**
   * ```xml
   * <d:blob d:size="16">0000010002000300 0000010002000300</d:blob>
   * ```
   */
  BIN_ELEMENT_TYPE_BLOB      = 0x42,
  /**
   * ```xml
   * <d:nil/>
   * ```
   */
  BIN_ELEMENT_TYPE_NULL      = 0x4e,
  /**
   * ```xml
   * <name id="123">
   * ```
   */
  BIN_ELEMENT_TYPE_OPENING   = 0x50,
  /**
   * ```xml
   * <name d:type="ref">123</name>
   * ```
   */
  BIN_ELEMENT_TYPE_REFERENCE = 0x52,
  /**
   * ```xml
   * <name d:type="bool">1</name>
   * ```
   * ```xml
   * <name d:type="cDeltaString">abc</name>
   * ```
   * ```xml
   * <name d:type="sFloat32" d:alt_encoding="000000000000f03f" d:precision="string">1</name>
   * ```
   * ```xml
   * <name d:type="sInt8">127</name>
   * ```
   * ```xml
   * <name d:type="sInt16">32767</name>
   * ```
   * ```xml
   * <name d:type="sInt32">2147483647</name>
   * ```
   * ```xml
   * <name d:type="sInt64">9223372036854775807</name>
   * ```
   * ```xml
   * <name d:type="sUInt8">255</name>
   * ```
   * ```xml
   * <name d:type="sUInt16">65535</name>
   * ```
   * ```xml
   * <name d:type="sUInt32">4294967295</name>
   * ```
   * ```xml
   * <name d:type="sUInt64">18446744073709551615</name>
   * ```
   */
  BIN_ELEMENT_TYPE_VALUE     = 0x56,
  /**
   * ```xml
   * </name>
   * ```
   */
  BIN_ELEMENT_TYPE_CLOSING   = 0x70,
} BinElementType;

typedef enum RailWorksDataType
{
  /**
   * int
   */
  RAILWORKS_DATA_TYPE_BOOL,
  /**
   * char *
   */
  RAILWORKS_DATA_TYPE_C_DELTA_STRING,
  /**
   * float
   */
  RAILWORKS_DATA_TYPE_S_FLOAT32,
  /**
   * char
   */
  RAILWORKS_DATA_TYPE_S_INT8,
  /**
   * short
   */
  RAILWORKS_DATA_TYPE_S_INT16,
  /**
   * int
   */
  RAILWORKS_DATA_TYPE_S_INT32,
  /**
   * long long
   */
  RAILWORKS_DATA_TYPE_S_INT64,
  /**
   * unsigned char
   */
  RAILWORKS_DATA_TYPE_S_U_INT8,
  /**
   * unsigned short
   */
  RAILWORKS_DATA_TYPE_S_U_INT16,
  /**
   * unsigned int
   */
  RAILWORKS_DATA_TYPE_S_U_INT32,
  /**
   * unsigned long long
   */
  RAILWORKS_DATA_TYPE_S_U_INT64,
} RailWorksDataType;

typedef struct BinElement BinElement;

char *railworks_data_type_to_string (RailWorksDataType type);

RailWorksDataType string_to_railworks_data_type (const char *string);

#endif
