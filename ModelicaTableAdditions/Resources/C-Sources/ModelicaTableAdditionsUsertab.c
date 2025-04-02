/* ModelicaTableAdditionsUsertab.c - A dummy usertab function

   Copyright (C) 2013-2025, Modelica Association and contributors
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/

/* The usertab function needs to be in a separate object or clang/gcc
   optimize the code in such a way that the user-defined usertab gets
   sent the wrong input.

   NOTE: If a dummy usertab is included in your code, you may be unable
   to also provide a user-defined usertab. If you use dynamic linking
   this is sometimes possible: when the simulation executable provides
   a usertab object, it will be part of the table of loaded objects and
   when later loading the shared object version of ModelicaStandardTables,
   the dummy usertab will not be loaded by the dynamic linker; this is
   what can confuse C-compilers and why this function is in a separate
   file).

   The interface of usertab is defined in ModelicaStandardTables.c
 */

#include "ModelicaUtilities.h"

#if defined(DUMMY_FUNCTION_USERTAB)
#if (defined(__clang__) || defined(__GNUC__)) && !(defined(__apple_build_version__) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__))
int usertabadditions(char* tableName, int nipo, int dim[], int* colWise,
            double** table) __attribute__ ((weak, alias ("dummy_additions_usertab")));
#define USERTAB_NAME dummy_additions_usertab
#else
#define USERTAB_NAME usertabadditions
#endif /* clang/gcc weak linking */
int USERTAB_NAME(char* tableName, int nipo, int dim[], int* colWise,
                 double** table) {
    ModelicaError("Function \"usertabadditions\" is not implemented\n");
    return 1; /* Error */
}
#endif /* #if defined(DUMMY_FUNCTION_USERTAB) */
