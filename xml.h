#ifndef XML_H
#define XML_H

typedef struct _XmlAttribute XmlAttribute;

typedef struct _XmlDocument XmlDocument;

typedef struct _XmlName XmlName;

typedef struct _XmlNode XmlNode;

struct _XmlAttribute
{
  XmlName *name;
  char    *value;
};

struct _XmlDocument
{
  XmlNode *root;
};

struct _XmlName
{
  char *prefix;
  char *local;
};

struct _XmlNode
{
  XmlName      *name;
  char         *value;
  XmlNode      *parent;
  XmlAttribute *attributes;
  XmlNode      *children;
};

#endif
