#include <stdio.h>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#define PLUG_IN_AUTHOR "Thomas Clark"
#define PLUG_IN_BINARY "file-tgpcdx"
#define PLUG_IN_COPYRIGHT "Copyright (C) 2025 Thomas Clark. All rights reserved."
#define PLUG_IN_ROLE "gimp-file-tgpcdx"
#define PLUG_IN_VERSION "1.0.0"

static void query(void);

static void run(const gchar *name, gint nparams, const GimpParam *param,
                gint *nreturn_vals, GimpParam **return_vals);

const GimpPlugInInfo PLUG_IN_INFO = {NULL, NULL, query, run};

int main(void) {
  printf("Hello, World!\n");
  return 0;
}