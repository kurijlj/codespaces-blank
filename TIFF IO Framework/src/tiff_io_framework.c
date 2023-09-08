/* ==========================================================================
 *  Copyright (C) <yyyy> Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of <PROGRAM_NAME>.
 *
 * <PROGRAM_NAME> is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * <PROGRAM_NAME> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */


/* ==========================================================================
 *
 * yyyy-mm-dd Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * <TIFF_IO_FRAMEWORK>.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 *
 * References (this section should be deleted in the release version)
 *
 * * For coding style visit GNU Coding Standards page at
 *   <https://www.gnu.org/prep/standards/html_node/index.html>.
 *
 * * For command line arguments parsing using argparse consult documentation
 *   and examples at <https://github.com/cofyc/argparse>.
 * 
 * * For how to use GNU Scientific Library consult documentation and examples
 *   at <https://www.gnu.org/software/gsl/doc/html/index.html>.
 * 
 * * For how to use libtiff consult documentation and examples at
 *   <http://www.libtiff.org/libtiff.html>.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* External libraries headers */
#include <argparse.h>
#include <gsl/gsl_math.h>
#include <tiffiop.h>


/* ==========================================================================
 * Macros definitions section
 * ========================================================================== */

#define APP_NAME             "tiff_io_framework"
#define APP_VERSION          "0.1"
#define APP_AUTHOR           "Ljubomir Kurij"
#define APP_EMAIL            "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR   "yyyy"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE          "GPLv3+"
#define APP_LICENSE_URL      "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION      "a versatile framework for constructing CLI apps "\
                             "in C"
#ifdef _WIN32
#define APP_USAGE_A          APP_NAME ".exe [OPTION]..."
#else
#define APP_USAGE_A          APP_NAME " [OPTION]..."
#endif  /* End of platform specific macro definition */
#define APP_EPILOGUE         "\nReport bugs to <" APP_EMAIL ">."

#define TIME_STAMP_LEN       20


/* ==========================================================================
 * Global variables section
 * ========================================================================== */

static const char *const kUsages[] = {
    APP_USAGE_A,
    NULL,
};
static TIFFErrorHandler old_error_handler = NULL;

#define DEFAULT_MAX_MALLOC (256 * 1024 * 1024)
/* malloc size limit (in bytes)
 * disabled when set to 0 */
static tmsize_t maxMalloc = DEFAULT_MAX_MALLOC;


/* ==========================================================================
 * Utility function declarations
 * ========================================================================== */

static int short_usage(struct argparse *self,
        const struct argparse_option *option);
static int version_info(struct argparse *self,
        const struct argparse_option *option);
static void custom_error_handler(const char *module,
        const char *fmt, va_list ap);


/* ==========================================================================
 * Main module
 * ========================================================================== */

int main(int argc, char **argv) {

    int usage = 0;
    int version = 0;
    char *in_file = NULL;
    char *out_file = NULL;

    /* Define command line options */
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("general options"),
        OPT_BOOLEAN(
                    '\0',
                    "usage",
                    &usage,
                    "give a short usage message",
                    &short_usage,
                    0,
                    0
                   ),
        OPT_BOOLEAN(
                    'V',
                    "version",
                    &version,
                    "print program version",
                    &version_info,
                    0,
                    0
                   ),
        OPT_GROUP("TIFF IO options"),
        OPT_STRING(
                   'r',
                   "read-from-file",
                   &in_file,
                   "TIFF file to read from",
                   NULL,
                   0,
                   0
                  ),
        OPT_STRING(
                   'w',
                   "write-to-file",
                   &out_file,
                   "TIFF file to write to",
                   NULL,
                   0,
                   0
                  ),
        OPT_END(),
    };

    /* Parse command line arguments */
    struct argparse argument_parser;
    argparse_init(&argument_parser, options, kUsages, 0);
    argparse_describe(&argument_parser, APP_DESCRIPTION, APP_EPILOGUE);
    argc = argparse_parse(&argument_parser, argc, argv);

    /* Check if usage or version options were given */
    if (usage != 0 || version != 0) {
        exit(EXIT_SUCCESS);

    }

    /* Main module code */
    int status = EXIT_SUCCESS;

    /* const char* time_stamp = __DATE__ " " __TIME__; */
    char time_stamp[TIME_STAMP_LEN] = "yyyy-mm-dd hh:mm:ss";
    time_t t = time(NULL);
    TIFF *in  = NULL;
    TIFF *out = NULL;

    status = EXIT_SUCCESS;

    t = time(NULL);
    strftime(
             time_stamp,
             TIME_STAMP_LEN,
             "%Y-%m-%d %H:%M:%S",
             localtime(&t)
            );
    fprintf(
            stderr,
            "%s: %s: Start of main program execution ...\n",
            time_stamp,
            APP_NAME
        );

    old_error_handler = TIFFSetErrorHandler(custom_error_handler);

    if (NULL != in_file) {
        TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
        if (NULL == opts) {
            status = EXIT_FAILURE;

        } else {
            TIFFOpenOptionsSetMaxSingleMemAlloc(opts, maxMalloc);
            in = TIFFOpenExt(in_file, "rh", opts);
            TIFFClose(in);
            TIFFOpenOptionsFree(opts);

        }

    } else if (NULL != out_file) {
        TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
        if (NULL == opts) {
            status = EXIT_FAILURE;

        } else {
            TIFFOpenOptionsSetMaxSingleMemAlloc(opts, maxMalloc);
            out = TIFFOpenExt(out_file, "w", opts);
            TIFFClose(out);
            TIFFOpenOptionsFree(opts);

        }

    } else {
        /* No arguments were given */
        status = EXIT_FAILURE;
        t = time(NULL);
        strftime(
                 time_stamp,
                 TIME_STAMP_LEN,
                 "%Y-%m-%d %H:%M:%S",
                 localtime(&t)
                );
        fprintf(
                stderr,
                "%s: %s: Invalid call to program.\n",
                time_stamp,
                APP_NAME
            );
        short_usage(&argument_parser, options);
        /* printf("%s: %s: PI = %f\n", time_stamp, APP_NAME, M_PI); */

    }

    t = time(NULL);
    strftime(
             time_stamp,
             TIME_STAMP_LEN,
             "%Y-%m-%d %H:%M:%S",
             localtime(&t)
            );

    if (EXIT_SUCCESS == status) {
        fprintf(
                stderr,
                "%s: %s: Main program finshed with: Success.\n",
                time_stamp,
                APP_NAME
            );

    } else {
        fprintf(
                stderr,
                "%s: %s: Main program finished with: Errors.\n",
                time_stamp,
                APP_NAME
            );

    }

    return status;

}


/* ==========================================================================
 * Utility function definitions
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: short_usage(
 *              struct argparse *self,
 *              const struct argparse_option *option
 *              )
 * --------------------------------------------------------------------------
 * 
 * Description: Print a short usage message
 * 
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure 
 * 
 * Returns: Number of characters printed
 * 
 * -------------------------------------------------------------------------- */
static int short_usage(struct argparse *self,
        const struct argparse_option *option) {
    #ifdef _WIN32
    return fprintf(stdout, "%s %s\n%s%s%s\n", 
        "Usage:", APP_USAGE_A,
        "Try `", APP_NAME, ".exe -h' for more information."
        );
    #else
    return fprintf(stdout, "%s %s\n%s%s%s\n", 
        "Usage:", APP_USAGE_A,
        "Try `", APP_NAME, " -h' for more information."
        );
    #endif  /* End of platform specific code */

}

/* --------------------------------------------------------------------------
 * Function: version_info(
 *              struct argparse *self,
 *              const struct argparse_option *option
 *              )
 * --------------------------------------------------------------------------
 * 
 * Description: Print program version information
 * 
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure 
 * 
 * Returns: Number of characters printed
 * 
 * -------------------------------------------------------------------------- */
static int version_info(struct argparse *self,
        const struct argparse_option *option) {
    return fprintf(stdout, "%s %s %s %s %s\n%s %s: %s <%s>\n%s\n%s\n",
            APP_NAME, APP_VERSION, "Copyright (c)",
            APP_COPYRIGHT_YEAR, APP_AUTHOR,
            "License", APP_LICENSE, "GNU GPL version 3 or later",
            APP_LICENSE_URL,
            "This is free software: you are free "
            "to change and redistribute it.",
            "There is NO WARRANTY, to the extent permitted by law."
            );

}


static void custom_error_handler(const char *module,
        const char *fmt, va_list ap)
{
    if (old_error_handler)
        (*old_error_handler)(module, fmt, ap);

}
