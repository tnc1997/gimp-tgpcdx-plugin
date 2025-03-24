#include <stdio.h>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#define LOAD_PROC "file-tgpcdx-load"

#define PLUG_IN_AUTHOR    "Thomas Clark"
#define PLUG_IN_BINARY    "file-tgpcdx"
#define PLUG_IN_COPYRIGHT "Copyright (C) 2025 Thomas Clark"
#define PLUG_IN_ROLE      "gimp-file-tgpcdx"
#define PLUG_IN_VERSION   "1.0.0"

static void query (void);

static void run (const char      *name,
                 int              nparams,
                 const GimpParam *param,
                 int             *nreturn_vals,
                 GimpParam      **return_vals);

const GimpPlugInInfo PLUG_IN_INFO = { NULL, NULL, query, run };

static GimpParamDef load_args[] = {
  { GIMP_PDB_INT32,  "run_mode",     "Interactive, non-interactive" },
  { GIMP_PDB_STRING, "filename",     "The name of the file to load" },
  { GIMP_PDB_STRING, "raw_filename", "The name entered"             }
};

static GimpParamDef load_return_vals[] = {
  { GIMP_PDB_IMAGE, "image", "Output image" }
};

MAIN ()

static void
query (void)
{
  gimp_install_procedure (LOAD_PROC,
                          "Loads files in the TGPCDX file format",
                          "Loads files in the TGPCDX file format",
                          PLUG_IN_AUTHOR,
                          PLUG_IN_COPYRIGHT,
                          PLUG_IN_VERSION,
                          "TGPCDX image",
                          NULL,
                          GIMP_PLUGIN,
                          G_N_ELEMENTS (load_args),
                          G_N_ELEMENTS (load_return_vals),
                          load_args,
                          load_return_vals);

  gimp_register_load_handler (LOAD_PROC, "tgpcdx", NULL);
}
