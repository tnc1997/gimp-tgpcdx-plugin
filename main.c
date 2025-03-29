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
                 int              n_params,
                 const GimpParam *param,
                 int             *n_return_vals,
                 GimpParam      **return_vals);

static int load_image (const char *filename, GError **error);

static int read_prelude (unsigned char *buffer, FILE *file);

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

static void
run (const char      *name,
     int              n_params,
     const GimpParam *param,
     int             *n_return_vals,
     GimpParam      **return_vals)
{
  static GimpParam  values[2];
  GimpRunMode       run_mode;
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GError           *error  = NULL;

  run_mode = param[0].data.d_int32;

  *n_return_vals = 1;
  *return_vals   = values;

  values[0].type          = GIMP_PDB_STATUS;
  values[0].data.d_status = GIMP_PDB_EXECUTION_ERROR;

  if (strcmp (name, LOAD_PROC) == 0)
    {
      const int IMAGE_ID = load_image (param[1].data.d_string, &error);

      if (IMAGE_ID != -1)
        {
          *n_return_vals         = 2;
          values[1].type         = GIMP_PDB_IMAGE;
          values[1].data.d_image = IMAGE_ID;
        }
      else
        {
          status = GIMP_PDB_EXECUTION_ERROR;
        }
    }
  else
    {
      status = GIMP_PDB_CALLING_ERROR;
    }

  values[0].data.d_status = status;
}

static int
load_image (const gchar *filename, GError **error)
{
  gimp_progress_init_printf ("Opening '%s'", filename);

  // TODO: Read tgpcdx file.

  FILE *file = fopen (filename, "rb");

  if (file == NULL)
    {
      g_set_error (error, 0, 0, "Failed to open the file '%s'", filename);

      return -1;
    }

  int i, c;

  for (i = 0; (c = fgetc (file)) != EOF; i++)
    {
      printf ("%02x", c);

      if (i % 16 == 15)
        {
          putchar ('\n');
        }
      else if (i % 2 == 1)
        {
          putchar (' ');
        }
    }

  if (i % 16 != 0)
    {
      putchar ('\n');
    }

  // TODO: Convert tgpcdx to dds.

  // TODO: Write dds file.

  // TODO: Run file dds load procedure.

  // TODO: Handle return values.

  return -1;
}

static int
read_prelude (unsigned char *buffer, FILE *file)
{
  const unsigned char prelude[8] = { 0x53, 0x45, 0x52, 0x5a,
                                     0x00, 0x00, 0x01, 0x00 };

  for (int i = 0; i < sizeof (prelude); i++)
    {
      const unsigned char c = fgetc (file);

      if (c != prelude[i])
        {
          return -1;
        }

      buffer[i] = c;
    }

  return 0;
}
