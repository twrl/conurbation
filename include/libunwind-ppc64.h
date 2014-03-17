/* libunwind - a platform-independent unwind library
   Copyright (C) 2006-2007 IBM
   Contributed by
     Corey Ashford <cjashfor@us.ibm.com>
     Jose Flavio Aguilar Paulino <jflavio@br.ibm.com> <joseflavio@gmail.com>

   Copied from libunwind-x86_64.h, modified slightly for building
   frysk successfully on ppc64, by Wu Zhou <woodzltc@cn.ibm.com>
   Will be replaced when libunwind is ready on ppc64 platform.

This file is part of libunwind.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#ifndef LIBUNWIND_H
#define LIBUNWIND_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include <inttypes.h>
#include <ucontext.h>

#define UNW_TARGET		ppc64
#define UNW_TARGET_PPC64	1

#define _U_TDEP_QP_TRUE	0	/* see libunwind-dynamic.h  */

#if __WORDSIZE==32
typedef uint32_t unw_word_t;
typedef int32_t unw_sword_t;
#else
typedef uint64_t unw_word_t;
typedef int64_t unw_sword_t;
#endif

typedef long double unw_tdep_fpreg_t;

/*
 * Vector register (in PowerPC64 used for AltiVec registers)
 */
typedef struct {
    uint64_t halves[2];
} unw_tdep_vreg_t;

/*
 * To simplify this whole process, we are at least initially taking the
 * tack that UNW_PPC64_* map straight across to the .eh_frame column register
 * numbers.  These register numbers come from bg/q in /usr/include/asm/ptrace.h
 */

typedef enum
  {
    UNW_PPC64_R0=0,
    UNW_PPC64_R1, /* called STACK_POINTER in gcc */
    UNW_PPC64_R2,
    UNW_PPC64_R3,
    UNW_PPC64_R4,
    UNW_PPC64_R5,
    UNW_PPC64_R6,
    UNW_PPC64_R7,
    UNW_PPC64_R8,
    UNW_PPC64_R9,
    UNW_PPC64_R10,
    UNW_PPC64_R11, /* called STATIC_CHAIN in gcc */
    UNW_PPC64_R12,
    UNW_PPC64_R13,
    UNW_PPC64_R14,
    UNW_PPC64_R15,
    UNW_PPC64_R16,
    UNW_PPC64_R17,
    UNW_PPC64_R18,
    UNW_PPC64_R19,
    UNW_PPC64_R20,
    UNW_PPC64_R21,
    UNW_PPC64_R22,
    UNW_PPC64_R23,
    UNW_PPC64_R24,
    UNW_PPC64_R25,
    UNW_PPC64_R26,
    UNW_PPC64_R27,
    UNW_PPC64_R28,
    UNW_PPC64_R29,
    UNW_PPC64_R30,
    UNW_PPC64_R31, /* called HARD_FRAME_POINTER in gcc */

    UNW_PPC64_NIP = 32,
    UNW_PPC64_MSR = 33,
    UNW_PPC64_ORIG_R3 = 34,
    UNW_PPC64_CTR = 35,
    UNW_PPC64_LR = 36,
    UNW_PPC64_XER = 37,
    UNW_PPC64_CCR = 38,
    UNW_PPC64_SOFTE = 39,
    UNW_PPC64_TRAP = 40,
    UNW_PPC64_DAR = 41,
    UNW_PPC64_DSISR = 42,
    UNW_PPC64_RESULT = 43,
    UNW_PPC64_REGS_COUNT = 44,
    UNW_PPC64_ARG_POINTER,

    UNW_PPC64_F0 = 48,
    UNW_PPC64_F1,
    UNW_PPC64_F2,
    UNW_PPC64_F3,
    UNW_PPC64_F4,
    UNW_PPC64_F5,
    UNW_PPC64_F6,
    UNW_PPC64_F7,
    UNW_PPC64_F8,
    UNW_PPC64_F9,
    UNW_PPC64_F10,
    UNW_PPC64_F11,
    UNW_PPC64_F12,
    UNW_PPC64_F13,
    UNW_PPC64_F14,
    UNW_PPC64_F15,
    UNW_PPC64_F16,
    UNW_PPC64_F17,
    UNW_PPC64_F18,
    UNW_PPC64_F19,
    UNW_PPC64_F20,
    UNW_PPC64_F21,
    UNW_PPC64_F22,
    UNW_PPC64_F23,
    UNW_PPC64_F24,
    UNW_PPC64_F25,
    UNW_PPC64_F26,
    UNW_PPC64_F27,
    UNW_PPC64_F28,
    UNW_PPC64_F29,
    UNW_PPC64_F30,
    UNW_PPC64_F31,
    UNW_PPC64_FPSCR = ( UNW_PPC64_F0 + 32 ),
    /* Note that there doesn't appear to be an .eh_frame register column
       for the FPSCR register.  I don't know why this is.  Since .eh_frame
       info is what this implementation uses for unwinding, we have no way
       to unwind this register, and so we will not expose an FPSCR register
       number in the libunwind API.
     */

    UNW_PPC64_V0 = 82, /* each Vector reg occupies 2 slots in 64-bit */
    UNW_PPC64_V1 = 84,
    UNW_PPC64_V2 = 86,
    UNW_PPC64_V3 = 88,
    UNW_PPC64_V4 = 90,
    UNW_PPC64_V5 = 92,
    UNW_PPC64_V6 = 94,
    UNW_PPC64_V7 = 96,
    UNW_PPC64_V8 = 98,
    UNW_PPC64_V9 = 100,
    UNW_PPC64_V10 = 102,
    UNW_PPC64_V11 = 104,
    UNW_PPC64_V12 = 106,
    UNW_PPC64_V13 = 108,
    UNW_PPC64_V14 = 110,
    UNW_PPC64_V15 = 112,
    UNW_PPC64_V16 = 114,
    UNW_PPC64_V17 = 116,
    UNW_PPC64_V18 = 118,
    UNW_PPC64_V19 = 120,
    UNW_PPC64_V20 = 122,
    UNW_PPC64_V21 = 124,
    UNW_PPC64_V22 = 126,
    UNW_PPC64_V23 = 128,
    UNW_PPC64_V24 = 130,
    UNW_PPC64_V25 = 132,
    UNW_PPC64_V26 = 134,
    UNW_PPC64_V27 = 136,
    UNW_PPC64_V28 = 138,
    UNW_PPC64_V29 = 140,
    UNW_PPC64_V30 = 142,
    UNW_PPC64_V31 = 144,
// 146 is unused
    UNW_PPC64_VSCR = (UNW_PPC64_V0 + 32*2 + 1), //147
    UNW_PPC64_VRSAVE = (UNW_PPC64_V0 + 33*2),   //148
/*
 *  * Only store first 32 VSRs here. The second 32 VSRs in VR0-31
 *   */
    UNW_PPC64_VSR0 = 150,     /* each VSR reg occupies 2 slots in 64-bit */
    UNW_PPC64_VSR1 = 152,
    UNW_PPC64_VSR2 = 154,
    UNW_PPC64_VSR3 = 156,
    UNW_PPC64_VSR4 = 158,
    UNW_PPC64_VSR5 = 160,
    UNW_PPC64_VSR6 = 162,
    UNW_PPC64_VSR7 = 164,
    UNW_PPC64_VSR8 = 166,
    UNW_PPC64_VSR9 = 168,
    UNW_PPC64_VSR10 = 170,
    UNW_PPC64_VSR11 = 172,
    UNW_PPC64_VSR12 = 174,
    UNW_PPC64_VSR13 = 176,
    UNW_PPC64_VSR14 = 178,
    UNW_PPC64_VSR15 = 180,
    UNW_PPC64_VSR16 = 182,
    UNW_PPC64_VSR17 = 184,
    UNW_PPC64_VSR18 = 186,
    UNW_PPC64_VSR19 = 188,
    UNW_PPC64_VSR20 = 190,
    UNW_PPC64_VSR21 = 192,
    UNW_PPC64_VSR22 = 194,
    UNW_PPC64_VSR23 = 196,
    UNW_PPC64_VSR24 = 198,
    UNW_PPC64_VSR25 = 200,
    UNW_PPC64_VSR26 = 202,
    UNW_PPC64_VSR27 = 204,
    UNW_PPC64_VSR28 = 206,
    UNW_PPC64_VSR29 = 208,
    UNW_PPC64_VSR30 = 210,
    UNW_PPC64_VSR31 = 212,

#define UNW_PPC64_REGS_AMOUNT 214

    UNW_TDEP_LAST_REG = UNW_PPC64_NIP, // maybe it should be some some more registers to restore

    UNW_TDEP_IP = UNW_PPC64_NIP,
    UNW_TDEP_SP = UNW_PPC64_R1,
    UNW_TDEP_EH = UNW_PPC64_R12,
  }
ppc64_regnum_t;

#include "dwarf-config.h"
#if DWARF_NUM_PRESERVED_REGS != UNW_PPC64_REGS_AMOUNT
#error DWARF_NUM_PRESERVED_REGS must be equal to UNW_PPC64_REGS_AMOUNT
#endif

/*
 * This needs to be big enough to accommodate "struct cursor", while
 * leaving some slack for future expansion.  Changing this value will
 * require recompiling all users of this library.  Stack allocation is
 * relatively cheap and unwind-state copying is relatively rare, so we want
 * to err on making it rather too big than too small.
 *
 * UNW_TDEP_CURSOR_LEN is in terms of unw_word_t size.  Since we have UNW_LAST_REG
 * elements in the loc array, each sized 2 * unw_word_t(see struct dwarf_loc_t in dwarf-config.h), 
 * plus the rest of the cursor struct (see struct dwarf_cursor_t in include/dwarf.h)
 */

#define UNW_TDEP_CURSOR_LEN (128 + UNW_PPC64_REGS_AMOUNT * 2)

/*
 * According to David Edelsohn, GNU gcc uses R3, R4, R5, and maybe R6 for
 * passing parameters to exception handlers.
 */

#define UNW_TDEP_NUM_EH_REGS	4

typedef struct unw_tdep_save_loc
  {
    /* Additional target-dependent info on a save location.  */
  }
unw_tdep_save_loc_t;

/* On ppc64, we can directly use ucontext_t as the unwind context.  */
typedef ucontext_t unw_tdep_context_t;

/* XXX this is not ideal: an application should not be prevented from
   using the "getcontext" name just because it's using libunwind.  We
   can't just use __getcontext() either, because that isn't exported
   by glibc...  */
#define unw_tdep_getcontext(uc)		(getcontext (uc), 0)

#include "libunwind-dynamic.h"

typedef struct
  {
    /* no ppc64-specific auxiliary proc-info */
  }
unw_tdep_proc_info_t;

#include "libunwind-common.h"

#define unw_tdep_is_fpreg		UNW_ARCH_OBJ(is_fpreg)
extern int unw_tdep_is_fpreg (int);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* LIBUNWIND_H */
