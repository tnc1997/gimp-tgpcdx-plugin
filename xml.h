#ifndef XML_H
#define XML_H

typedef struct _XmlAttribute XmlAttribute;

typedef struct _XmlName XmlName;

struct _XmlAttribute
{
  XmlName *name;
  char    *value;
};

struct _XmlName
{
  char *prefix;
  char *local;
};

#endif
