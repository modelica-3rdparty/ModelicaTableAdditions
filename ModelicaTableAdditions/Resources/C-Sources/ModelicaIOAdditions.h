/* ModelicaIOAdditions.h - Array I/O functions header

   Copyright (C) 2016-2024, Modelica Association and contributors
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* The following #define's are available.

   NO_FILE_SYSTEM : A file system is not present (e.g. on dSPACE or xPC).
   NO_LOCALE      : locale.h is not present (e.g. on AVR).
   NO_MATIO       : ModelicaMatio.h is not present.
   MODELICA_EXPORT: Prefix used for function calls. If not defined, blank is used
                    Useful definition:
                    - "__declspec(dllexport)" if included in a DLL and the
                      functions shall be visible outside of the DLL

   Changelog:
      Mar. 08, 2017: by Thomas Beutlich, ESI ITI GmbH
                     Added ModelicaIO_readRealTable from ModelicaStandardTables
                     (ticket #2192)

      Mar. 03, 2016: by Thomas Beutlich, ITI GmbH and Martin Otter, DLR
                     Implemented a first version (ticket #1856)
*/

#ifndef MODELICA_IOADDITIONS_H_
#define MODELICA_IOADDITIONS_H_

#include <stdlib.h>

#if !defined(MODELICA_EXPORT)
#if defined(__cplusplus)
#define MODELICA_EXPORT extern "C"
#else
#define MODELICA_EXPORT
#endif
#endif

/*
 * Non-null pointers and esp. null-terminated strings need to be passed to
 * external functions.
 *
 * The following macros handle nonnull attributes for GNU C and Microsoft SAL.
 */
#undef MODELICA_NONNULLATTR
#if defined(__GNUC__)
#define MODELICA_NONNULLATTR __attribute__((nonnull))
#else
#define MODELICA_NONNULLATTR
#endif
#if !defined(__ATTR_SAL)
#undef _In_
#undef _In_z_
#undef _Inout_
#undef _Out_
#define _In_
#define _In_z_
#define _Inout_
#define _Out_
#endif

MODELICA_EXPORT double* ModelicaIOAdditions_readRealTable(_In_z_ const char* fileName,
                                 _In_z_ const char* tableName,
                                 _Out_ size_t* m, _Out_ size_t* n,
                                 int verbose, _In_z_ const char* delimiter,
                                 int nHeaderLines) MODELICA_NONNULLATTR;
  /* Read matrix and its dimensions from file
     Note: Only called from ModelicaStandardTables, but impossible to be called
     from a Modelica environment

     -> fileName: Name of file
     -> matrixName: Name of matrix
     -> m: Number of rows
     -> n: Number of columns
     -> verbose: Print message that file is loading
     -> delimiter: Column delimiter character (CSV file only)
     -> nHeaderLines: Number of header lines to ignore (CSV file only)
     <- RETURN: Array of dimensions m by n
  */

MODELICA_EXPORT void ModelicaIOAdditions_freeRealTable(double* table);
  /* Free table
     Note: Only called from ModelicaStandardTables to free the allocated memory by
     ModelicaIOAdditions_readRealTable
  */

#endif
