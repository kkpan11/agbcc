/* Definitions of target machine for GNU compiler, for ARM/Thumb.
   Copyright (C) 1996, 1997, 1998, 1999, 2002 Free Software Foundation, Inc.
   The basis of this contribution was generated by
   		Richard Earnshaw, Advanced RISC Machines Ltd

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* ??? The files thumb.{c,h,md} are all seriously lacking comments.  */

/* ??? The files thumb.{c,h,md} need to be reviewed by an experienced
   gcc hacker in their entirety.  */

/* ??? The files thumb.{c,h,md} and tcoff.h are all separate from the arm
   files, which will lead to many maintenance problems.  These files are
   likely missing all bug fixes made to the arm port since they diverged.  */

/* ??? Many patterns in the md file accept operands that will require a
   reload.  These should be eliminated if possible by tightening the
   predicates and/or constraints.  This will give faster/smaller code.  */

/* ??? There is no pattern for the TST instuction.  Check for other unsupported
   instructions.  */

#define TARGET_VERSION  fputs (" (ARM/THUMB:generic)", stderr);

#define ARM_FLAG_THUMB				0x1000	/* same as in arm.h */
#define THUMB_FLAG_CALLER_SUPER_INTERWORKING	0x80000 

/* Nonzero if all call instructions should be indirect.  */
#define ARM_FLAG_LONG_CALLS	(0x10000) /* same as in arm.h */


/* Run-time compilation parameters selecting different hardware/software subsets.  */
extern int target_flags;
#define TARGET_DEFAULT          0 /* ARM_FLAG_THUMB */
#define TARGET_THUMB_INTERWORK	(target_flags & ARM_FLAG_THUMB)

/* Set if calls via function pointers should assume that their
   destination is non-Thumb aware.  */
#define TARGET_CALLER_INTERWORKING	\
     (target_flags & THUMB_FLAG_CALLER_SUPER_INTERWORKING)

#define TARGET_LONG_CALLS		(target_flags & ARM_FLAG_LONG_CALLS)

/* SUBTARGET_SWITCHES is used to add flags on a per-config basis. */
#ifndef SUBTARGET_SWITCHES
#define SUBTARGET_SWITCHES
#endif

#define TARGET_SWITCHES                                 	\
{                                                       	\
  {"thumb-interwork",		    ARM_FLAG_THUMB},		\
  {"no-thumb-interwork",           -ARM_FLAG_THUMB},		\
  {"caller-super-interworking",	    THUMB_FLAG_CALLER_SUPER_INTERWORKING}, \
  {"no-caller-super-interworking", -THUMB_FLAG_CALLER_SUPER_INTERWORKING}, \
  {"long-calls",		ARM_FLAG_LONG_CALLS,		\
   "Generate all call instructions as indirect calls"},		\
  {"no-long-calls",	       -ARM_FLAG_LONG_CALLS, ""},	\
  SUBTARGET_SWITCHES						\
  {"",                          TARGET_DEFAULT}         	\
}

#define TARGET_OPTIONS						\
{								\
  { "structure-size-boundary=", & structure_size_string }, 	\
}

#define REGISTER_PREFIX ""

#define CAN_DEBUG_WITHOUT_FP 1

#define ASM_APP_ON  ""
#define ASM_APP_OFF "\t.code\t16\n"

/* Output a gap.  In fact we fill it with nulls.  */
#define ASM_OUTPUT_SKIP(STREAM, NBYTES)  \
  fprintf ((STREAM), "\t.space\t%u\n", (NBYTES))

/* This is how to output an assembler line
   that says to advance the location counter
   to a multiple of 2**LOG bytes.  */

#ifdef OLD_ASM

#define ASM_OUTPUT_ALIGN(STREAM,LOG)               \
{                                                  \
    if ((LOG) > 0)                                 \
        fprintf (STREAM, "\t.align\t%d\n", (LOG)); \
}

#else

#define ASM_OUTPUT_ALIGN(STREAM,LOG)                  \
{                                                     \
    if ((LOG) > 0)                                    \
        fprintf (STREAM, "\t.align\t%d, 0\n", (LOG)); \
}

#endif

/* Output a common block */
#define ASM_OUTPUT_COMMON(STREAM, NAME, SIZE, ROUNDED)  		\
  (fprintf ((STREAM), "\t.comm\t"), 		     			\
   assemble_name ((STREAM), (NAME)),		     			\
   fprintf((STREAM), ", %d\t%s %d\n", (ROUNDED), (ASM_COMMENT_START), (SIZE)))

#define ASM_GENERATE_INTERNAL_LABEL(STRING,PREFIX,NUM)        \
  sprintf ((STRING), "*%s%s%d", (LOCAL_LABEL_PREFIX), (PREFIX), (NUM))

/* This is how to output an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.  */
#define ASM_OUTPUT_INTERNAL_LABEL(STREAM,PREFIX,NUM)			\
  fprintf ((STREAM), "%s%s%d:\n", (LOCAL_LABEL_PREFIX), (PREFIX), (NUM))

/* This is how to output a label which precedes a jumptable.  Since
   instructions are 2 bytes, we need explicit alignment here.  */

#define ASM_OUTPUT_CASE_LABEL(FILE,PREFIX,NUM,JUMPTABLE)		\
  do {									\
    ASM_OUTPUT_ALIGN (FILE, 2);						\
    ASM_OUTPUT_INTERNAL_LABEL (FILE, PREFIX, NUM);			\
  } while (0)

/* This says how to define a local common symbol (ie, not visible to
   linker).  */
#define ASM_OUTPUT_LOCAL(STREAM, NAME, SIZE, ROUNDED)			\
  (fprintf((STREAM),"\n\t.lcomm\t"),                                    \
   assemble_name((STREAM),(NAME)),                                      \
   fprintf((STREAM),",%u\n",(SIZE)))

/* Output a reference to a label.  */
#define ASM_OUTPUT_LABELREF(STREAM,NAME)  \
  fprintf ((STREAM), "%s", (NAME))

/* This is how to output an assembler line for a numeric constant byte.  */
#define ASM_OUTPUT_BYTE(STREAM,VALUE)					\
  fprintf ((STREAM), "\t.byte\t0x%x\n", (VALUE))

#define ASM_OUTPUT_INT(STREAM,VALUE)					\
{									\
  fprintf (STREAM, "\t.word\t");					\
  output_addr_const (STREAM, (VALUE));					\
  fprintf (STREAM, "\n");						\
}

#define ASM_OUTPUT_SHORT(STREAM,VALUE)					\
{									\
  fprintf (STREAM, "\t.short\t");					\
  output_addr_const (STREAM, (VALUE));					\
  fprintf (STREAM, "\n");						\
}

#define ASM_OUTPUT_CHAR(STREAM,VALUE)					\
{									\
  fprintf (STREAM, "\t.byte\t");					\
  output_addr_const (STREAM, (VALUE));					\
  fprintf (STREAM, "\n");						\
}

#define ASM_OUTPUT_DOUBLE(STREAM, VALUE)  				\
do { char dstr[30];							\
     long l[2];								\
     REAL_VALUE_TO_TARGET_DOUBLE (VALUE, l);				\
     REAL_VALUE_TO_DECIMAL (VALUE, "%.14g", dstr);			\
     fprintf (STREAM, "\t.long 0x%lx, 0x%lx\t%s double %s\n", l[0],	\
	      l[1], ASM_COMMENT_START, dstr);				\
   } while (0)

#define ASM_OUTPUT_FLOAT(STREAM, VALUE)					\
do { char dstr[30];							\
     long l;								\
     REAL_VALUE_TO_TARGET_SINGLE (VALUE, l);				\
     REAL_VALUE_TO_DECIMAL (VALUE, "%.7g", dstr);			\
     fprintf (STREAM, "\t.word 0x%lx\t%s float %s\n", l,		\
	      ASM_COMMENT_START, dstr);					\
   } while (0);

/* Define results of standard character escape sequences.  */
#define TARGET_BELL	007
#define TARGET_BS	010
#define TARGET_TAB	011
#define TARGET_NEWLINE	012
#define TARGET_VT	013
#define TARGET_FF	014
#define TARGET_CR	015

/* This is how to output a string.  */
#define ASM_OUTPUT_ASCII(STREAM, STRING, LEN)				\
do {									\
  register int i, c, len = (LEN), cur_pos = 17;				\
  register unsigned char *string = (unsigned char *)(STRING);		\
  fprintf ((STREAM), "\t.ascii\t\"");					\
  for (i = 0; i < len; i++)						\
    {									\
      register int c = string[i];					\
									\
      switch (c)							\
	{								\
	case '\"':							\
	case '\\':							\
	  putc ('\\', (STREAM));					\
	  putc (c, (STREAM));						\
	  cur_pos += 2;							\
	  break;							\
									\
	case TARGET_NEWLINE:						\
	  fputs ("\\n", (STREAM));					\
	  if (i+1 < len							\
	      && (((c = string[i+1]) >= '\040' && c <= '~')		\
		  || c == TARGET_TAB))					\
	    cur_pos = 32767;		/* break right here */		\
	  else								\
	    cur_pos += 2;						\
	  break;							\
									\
	case TARGET_TAB:						\
	  fputs ("\\t", (STREAM));					\
	  cur_pos += 2;							\
	  break;							\
									\
	case TARGET_FF:							\
	  fputs ("\\f", (STREAM));					\
	  cur_pos += 2;							\
	  break;							\
									\
	case TARGET_BS:							\
	  fputs ("\\b", (STREAM));					\
	  cur_pos += 2;							\
	  break;							\
									\
	case TARGET_CR:							\
	  fputs ("\\r", (STREAM));					\
	  cur_pos += 2;							\
	  break;							\
									\
	default:							\
	  if (c >= ' ' && c < 0177)					\
	    {								\
	      putc (c, (STREAM));					\
	      cur_pos++;						\
	    }								\
	  else								\
	    {								\
	      fprintf ((STREAM), "\\%03o", c);				\
	      cur_pos += 4;						\
	    }								\
	}								\
									\
      if (cur_pos > 72 && i+1 < len)					\
	{								\
	  cur_pos = 17;							\
	  fprintf ((STREAM), "\"\n\t.ascii\t\"");			\
	}								\
    }									\
  fprintf ((STREAM), "\"\n");						\
} while (0)

/* Output and Generation of Labels */
#define ASM_OUTPUT_LABEL(STREAM,NAME) \
  (assemble_name ((STREAM), (NAME)),  \
   fprintf ((STREAM), ":\n"))

#define ASM_GLOBALIZE_LABEL(STREAM,NAME)      \
 (fprintf ((STREAM), "\t.globl\t"),           \
  assemble_name ((STREAM), (NAME)),           \
  fputc ('\n', (STREAM)))

/* Construct a private name.  */
#define ASM_FORMAT_PRIVATE_NAME(OUTVAR,NAME,NUMBER)  \
  ((OUTVAR) = (char *) alloca (strlen (NAME) + 10),  \
   sprintf ((OUTVAR), "%s.%d", (NAME), (NUMBER)))

/* Switch to the text or data segment.  */
#define TEXT_SECTION_ASM_OP  ".text"
#define DATA_SECTION_ASM_OP  ".data"
#define BSS_SECTION_ASM_OP   ".bss"

/* The assembler's names for the registers.  */
#ifndef REGISTER_NAMES
#define REGISTER_NAMES  \
{				                   \
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",  \
  "r8", "r9", "sl", "fp", "ip", "sp", "lr", "pc", "ap"   \
}
#endif

#ifndef ADDITIONAL_REGISTER_NAMES
#define ADDITIONAL_REGISTER_NAMES		\
{						\
  {"a1", 0},					\
  {"a2", 1},					\
  {"a3", 2},					\
  {"a4", 3},					\
  {"v1", 4},					\
  {"v2", 5},					\
  {"v3", 6},					\
  {"v4", 7},					\
  {"v5", 8},					\
  {"v6", 9},					\
  {"sb", 9},					\
  {"v7", 10},					\
  {"r10", 10},	/* sl */			\
  {"r11", 11},	/* fp */			\
  {"r12", 12},	/* ip */			\
  {"r13", 13},	/* sp */			\
  {"r14", 14},	/* lr */			\
  {"r15", 15}	/* pc */			\
}
#endif

/* The assembler's parentheses characters.  */
#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"

#ifndef ASM_COMMENT_START
#define ASM_COMMENT_START "@"
#endif

/* Output an element of a dispatch table.  */
#define ASM_OUTPUT_ADDR_VEC_ELT(STREAM,VALUE)  \
   fprintf (STREAM, "\t.word\t%sL%d\n", (LOCAL_LABEL_PREFIX), (VALUE))

#define ASM_OUTPUT_ADDR_DIFF_ELT(STREAM,BODY,VALUE,REL)  \
   fprintf (STREAM, "\tb\t%sL%d\n", (LOCAL_LABEL_PREFIX), (VALUE))

/* Storage Layout */

#define FLOAT_WORDS_BIG_ENDIAN 1

#define BITS_PER_UNIT 8
#define BITS_PER_WORD 32

#define UNITS_PER_WORD 4

#define POINTER_SIZE 32

#define PROMOTE_MODE(MODE,UNSIGNEDP,TYPE)	\
{						\
  if (GET_MODE_CLASS (MODE) == MODE_INT		\
      && GET_MODE_SIZE (MODE) < 4)		\
    {						\
      (UNSIGNEDP) = 1;				\
      (MODE) = SImode;				\
    }						\
}

#define PARM_BOUNDARY 32
#define STACK_BOUNDARY 32

#define FUNCTION_BOUNDARY 32
#define BIGGEST_ALIGNMENT 32

/* Make strings word-aligned so strcpy from constants will be faster.  */
#define CONSTANT_ALIGNMENT(EXP, ALIGN)  \
  (TREE_CODE (EXP) == STRING_CST        \
   && (ALIGN) < BITS_PER_WORD ? BITS_PER_WORD : (ALIGN))

#define EMPTY_FIELD_BOUNDARY 32

#define STRUCTURE_SIZE_BOUNDARY 32

/* Used when parsing command line option -mstructure_size_boundary.  */
extern char * structure_size_string;

#define STRICT_ALIGNMENT 1

#define TARGET_FLOAT_FORMAT IEEE_FLOAT_FORMAT


/* Layout of Source Language Data Types  */

#define TARGET_BELL	007
#define TARGET_BS	010
#define TARGET_TAB	011
#define TARGET_NEWLINE	012
#define TARGET_VT	013
#define TARGET_FF	014
#define TARGET_CR	015


/* Register Usage */

/* Note there are 16 hard registers on the Thumb.  We invent a 17th register
   which is assigned to ARG_POINTER_REGNUM, but this is later removed by
   elimination passes in the compiler.  */
#define FIRST_PSEUDO_REGISTER 17

/* ??? This is questionable.  */
#define FIXED_REGISTERS \
{			\
  0,0,0,0,		\
  0,0,0,0,		\
  0,0,0,1,		\
  0,1,1,1,1		\
}

/* ??? This is questionable.  */
#define CALL_USED_REGISTERS	\
{				\
  1,1,1,1,			\
  0,0,0,0,			\
  0,0,0,1,			\
  1,1,1,1,1			\
}

#define HARD_REGNO_NREGS(REGNO,MODE)		\
  ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1)	\
   / UNITS_PER_WORD)

/* ??? Probably should only allow DImode/DFmode in even numbered registers.  */
#define HARD_REGNO_MODE_OK(REGNO,MODE) ((GET_MODE_SIZE (MODE) > UNITS_PER_WORD) ? (REGNO < 7) : 1)

#define MODES_TIEABLE_P(MODE1,MODE2) 1

/* The NOARG_LO_REGS class is the set of LO_REGS that are not used for passing
   arguments to functions.  These are the registers that are available for
   spilling during reload.  The code in reload1.c:init_reload() will detect this
   class and place it into 'reload_address_base_reg_class'.  */

enum reg_class
{
  NO_REGS,
  NONARG_LO_REGS,
  LO_REGS,
  STACK_REG,
  BASE_REGS,
  HI_REGS,
  ALL_REGS,
  LIM_REG_CLASSES
};

#define GENERAL_REGS ALL_REGS

#define N_REG_CLASSES (int) LIM_REG_CLASSES

#define REG_CLASS_NAMES \
{			\
  "NO_REGS",		\
  "NONARG_LO_REGS",	\
  "LO_REGS",		\
  "STACK_REG",		\
  "BASE_REGS",		\
  "HI_REGS",		\
  "ALL_REGS"		\
}

#define REG_CLASS_CONTENTS	\
{				\
  0x00000,			\
  0x000f0,			\
  0x000ff,			\
  0x02000,			\
  0x020ff,			\
  0x0ff00,			\
  0x1ffff,			\
}

#define REGNO_REG_CLASS(REGNO)			\
 ((REGNO) == STACK_POINTER_REGNUM ? STACK_REG	\
  : (REGNO) < 8 ? ((REGNO) < 4 ? LO_REGS	\
		   : NONARG_LO_REGS)		\
  : HI_REGS)

#define BASE_REG_CLASS BASE_REGS

#define MODE_BASE_REG_CLASS(MODE) 		\
    ((MODE) != QImode && (MODE) != HImode 	\
     ? BASE_REGS : LO_REGS)

#define INDEX_REG_CLASS LO_REGS

/* When SMALL_REGISTER_CLASSES is nonzero, the compiler allows
   registers explicitly used in the rtl to be used as spill registers
   but prevents the compiler from extending the lifetime of these
   registers. */

#define SMALL_REGISTER_CLASSES 1

#define REG_CLASS_FROM_LETTER(C) \
  ((C) == 'l' ? LO_REGS		\
   : (C) == 'h' ? HI_REGS	\
   : (C) == 'b' ? BASE_REGS	\
   : (C) == 'k' ? STACK_REG	\
   : NO_REGS)

#define REGNO_OK_FOR_BASE_P(REGNO)				\
  ((REGNO) < 8							\
   || (REGNO) == STACK_POINTER_REGNUM				\
   || (unsigned) reg_renumber[REGNO] < 8			\
   || (unsigned) reg_renumber[REGNO] == STACK_POINTER_REGNUM)

#define REGNO_MODE_OK_FOR_BASE_P(REGNO, MODE)			\
  ((REGNO) < 8							\
   || (unsigned) reg_renumber[REGNO] < 8			\
   || (GET_MODE_SIZE (MODE) >= 4				\
       && ((REGNO) == STACK_POINTER_REGNUM			\
	   || (unsigned) reg_renumber[REGNO] == STACK_POINTER_REGNUM)))

#define REGNO_OK_FOR_INDEX_P(REGNO)		\
  ((REGNO) < 8					\
   || (unsigned) reg_renumber[REGNO] < 8)

/* ??? This looks suspiciously wrong.  */
/* We need to leave BASE_REGS reloads alone, in order to avoid caller_save
   lossage.  Caller_saves requests a BASE_REGS reload (caller_save_spill_class)
   and then later we verify that one was allocated.  If PREFERRED_RELOAD_CLASS
   says to allocate a LO_REGS spill instead, then this mismatch gives an
   abort.  Alternatively, this could be fixed by modifying BASE_REG_CLASS
   to be LO_REGS instead of BASE_REGS.  It is not clear what affect this
   change would have.  */
/* ??? This looks even more suspiciously wrong.  PREFERRED_RELOAD_CLASS
   must always return a strict subset of the input class.  Just blindly
   returning LO_REGS is safe only if the input class is a superset of LO_REGS,
   but there is no check for this.  Added another exception for NONARG_LO_REGS
   because it is not a superset of LO_REGS.  */
/* ??? We now use NONARG_LO_REGS for caller_save_spill_class, so the
   comments about BASE_REGS are now obsolete.  */
#define PREFERRED_RELOAD_CLASS(X,CLASS) \
  ((CLASS) == BASE_REGS || (CLASS) == NONARG_LO_REGS ? (CLASS)	\
   : LO_REGS)
/*
  ((CONSTANT_P ((X)) && GET_CODE ((X)) != CONST_INT		\
    && ! CONSTANT_POOL_ADDRESS_P((X))) ? NO_REGS		\
   : (GET_CODE ((X)) == CONST_INT				\
      && (HOST_WIDE_UINT) INTVAL ((X)) > 255) ? NO_REGS	\
   : LO_REGS) */

/* Must leave BASE_REGS and NONARG_LO_REGS reloads alone, see comment
   above.  */
#define SECONDARY_RELOAD_CLASS(CLASS,MODE,X)				\
   ((CLASS) != LO_REGS && (CLASS) != BASE_REGS && (CLASS) != NONARG_LO_REGS \
   ? ((true_regnum (X) == -1 ? LO_REGS					\
       : (true_regnum (X) + HARD_REGNO_NREGS (0, MODE) > 8) ? LO_REGS	\
       : NO_REGS)) 							\
   : NO_REGS)

#define CLASS_MAX_NREGS(CLASS,MODE) HARD_REGNO_NREGS(0,(MODE))

int thumb_shiftable_const ();

#define CONST_OK_FOR_LETTER_P(VAL,C)				\
  ((C) == 'I' ? (HOST_WIDE_UINT) (VAL) < 256		\
   : (C) == 'J' ? (VAL) > -256 && (VAL) <= 0			\
   : (C) == 'K' ? thumb_shiftable_const (VAL)			\
   : (C) == 'L' ? (VAL) > -8 && (VAL) < 8			\
   : (C) == 'M' ? ((HOST_WIDE_UINT) (VAL) < 1024	\
		   && ((VAL) & 3) == 0)				\
   : (C) == 'N' ? ((HOST_WIDE_UINT) (VAL) < 32)		\
   : (C) == 'O' ? ((VAL) >= -508 && (VAL) <= 508)		\
   : 0)

#define CONST_DOUBLE_OK_FOR_LETTER_P(VAL,C) 0

#define EXTRA_CONSTRAINT(X,C)						\
  ((C) == 'Q' ? (GET_CODE (X) == MEM					\
		 && GET_CODE (XEXP (X, 0)) == LABEL_REF) : 0)

/* Stack Layout and Calling Conventions */

#define STACK_GROWS_DOWNWARD 1

/* #define FRAME_GROWS_DOWNWARD 1 */

/* #define ARGS_GROW_DOWNWARD 1 */

#define STARTING_FRAME_OFFSET 0

#define FIRST_PARM_OFFSET(FNDECL) 0

/* Registers that address the stack frame */

#define STACK_POINTER_REGNUM  13	/* Defined by the TPCS.  */

#define FRAME_POINTER_REGNUM  7		/* TPCS defines this as 11 but it does not really mean it.  */

#define ARG_POINTER_REGNUM    16	/* A fake hard register that is eliminated later on.  */

#define STATIC_CHAIN_REGNUM 9

#define FRAME_POINTER_REQUIRED 0

#define ELIMINABLE_REGS				\
{{ARG_POINTER_REGNUM, STACK_POINTER_REGNUM},	\
 {ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM},	\
 {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}

/* On the Thumb we always want to perform the eliminations as we
   actually only have one real register pointing to the stashed
   variables: the stack pointer, and we never use the frame pointer.  */
#define CAN_ELIMINATE(FROM,TO)  1

/* Note:  This macro must match the code in thumb_function_prologue() in thumb.c.  */
#define INITIAL_ELIMINATION_OFFSET(FROM,TO,OFFSET)		\
{								\
  (OFFSET) = 0;							\
  if ((FROM) == ARG_POINTER_REGNUM)				\
    {								\
      int count_regs = 0;					\
      int regno;						\
      (OFFSET) += get_frame_size (); 				\
      for (regno = 8; regno < 13; regno++)			\
	if (regs_ever_live[regno] && ! call_used_regs[regno])	\
	  count_regs++;						\
      if (count_regs)						\
	(OFFSET) += 4 * count_regs;	 			\
      count_regs = 0;						\
      for (regno = 0; regno < 8; regno++)			\
	if (regs_ever_live[regno] && ! call_used_regs[regno])	\
	  count_regs++;						\
      if (count_regs || ! leaf_function_p () || far_jump_used_p())	\
	(OFFSET) += 4 * (count_regs + 1);			\
    }								\
  if ((TO) == STACK_POINTER_REGNUM)				\
    (OFFSET) += current_function_outgoing_args_size;		\
}

/* Passing Arguments on the stack */

#define PROMOTE_PROTOTYPES 1

#define ACCUMULATE_OUTGOING_ARGS 1

#define RETURN_POPS_ARGS(FUNDECL,FUNTYPE,SIZE) 0

#define FUNCTION_ARG(CUM,MODE,TYPE,NAMED)				\
 ((NAMED) ? ((CUM) >= 16 ? 0 : gen_rtx (REG, (MODE), (CUM) / 4))	\
  : 0)

#define FUNCTION_ARG_PARTIAL_NREGS(CUM,MODE,TYPE,NAMED)			\
 (((CUM) < 16 && (CUM) + (((MODE) == BLKmode)				\
			  ? int_size_in_bytes (TYPE)			\
			  : HARD_REGNO_NREGS (0, (MODE)) * 4) > 16)	\
  ? 4 - (CUM) / 4 : 0)

#define CUMULATIVE_ARGS int

#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT)		\
 ((CUM) = ((FNTYPE) && aggregate_value_p (TREE_TYPE (FNTYPE))) ? 4 : 0)

#define FUNCTION_ARG_ADVANCE(CUM,MODE,TYPE,NAMED)	\
 (CUM) += ((((MODE) == BLKmode)				\
	    ? int_size_in_bytes (TYPE)			\
	    : GET_MODE_SIZE (MODE)) + 3) & ~3

#define FUNCTION_ARG_REGNO_P(REGNO)	\
  ((REGNO) >=0 && (REGNO) <= 3)

#define FUNCTION_VALUE(VALTYPE,FUNC) gen_rtx (REG, TYPE_MODE (VALTYPE), 0)

#define LIBCALL_VALUE(MODE) gen_rtx (REG, (MODE), 0)

#define FUNCTION_VALUE_REGNO_P(REGNO) ((REGNO) == 0)

     /* How large values are returned */
/* A C expression which can inhibit the returning of certain function values
   in registers, based on the type of value. */
#define RETURN_IN_MEMORY(TYPE) thumb_return_in_memory (TYPE)
     
/* Define DEFAULT_PCC_STRUCT_RETURN to 1 if all structure and union return
   values must be in memory.  On the ARM, they need only do so if larger
   than a word, or if they contain elements offset from zero in the struct. */
#define DEFAULT_PCC_STRUCT_RETURN 0


#define STRUCT_VALUE_REGNUM 0

#define FUNCTION_PROLOGUE(FILE,SIZE) thumb_function_prologue((FILE),(SIZE))

#define FUNCTION_EPILOGUE(FILE,SIZE) thumb_function_epilogue((FILE),(SIZE))

/* Implementing the Varargs Macros */

#define SETUP_INCOMING_VARARGS(CUM,MODE,TYPE,PRETEND_SIZE,NO_RTL)	\
{									\
  extern int current_function_anonymous_args;				\
  current_function_anonymous_args = 1;					\
  if ((CUM) < 16)							\
    (PRETEND_SIZE) = 16 - (CUM);					\
}

/* Trampolines for nested functions */

/* Output assembler code for a block containing the constant parts of
   a trampoline, leaving space for the variable parts.

   On the Thumb we always switch into ARM mode to execute the trampoline.
   Why - because it is easier.  This code will always be branched to via
   a BX instruction and since the compiler magically generates the address
   of the function the linker has no opportunity to ensure that the
   bottom bit is set.  Thus the processor will be in ARM mode when it
   reaches this code.  So we duplicate the ARM trampoline code and add
   a switch into Thumb mode as well.
   
   On the ARM, (if r8 is the static chain regnum, and remembering that
   referencing pc adds an offset of 8) the trampoline looks like:
	   ldr 		r8, [pc, #0]
	   ldr		pc, [pc]
	   .word	static chain value
	   .word	function's address
   ??? FIXME: When the trampoline returns, r8 will be clobbered.  */
#define TRAMPOLINE_TEMPLATE(FILE)				\
{								\
  fprintf ((FILE), "\t.code 32\n");				\
  fprintf ((FILE), ".Ltrampoline_start:\n");			\
  fprintf ((FILE), "\tldr\t%s, [%spc, #8]\n",			\
	   reg_names[STATIC_CHAIN_REGNUM], REGISTER_PREFIX);	\
  fprintf ((FILE), "\tldr\t%sip, [%spc, #8]\n",			\
	   REGISTER_PREFIX, REGISTER_PREFIX);			\
  fprintf ((FILE), "\torr\t%sip, %sip, #1\n",                   \
	   REGISTER_PREFIX, REGISTER_PREFIX);                   \
  fprintf ((FILE), "\tbx\t%sip\n", REGISTER_PREFIX);	        \
  fprintf ((FILE), "\t.word\t0\n");				\
  fprintf ((FILE), "\t.word\t0\n");				\
  fprintf ((FILE), "\t.code 16\n");				\
}

/* Length in units of the trampoline for entering a nested function.  */
#define TRAMPOLINE_SIZE  24

/* Alignment required for a trampoline in units.  */
#define TRAMPOLINE_ALIGN  4

#define INITIALIZE_TRAMPOLINE(ADDR,FNADDR,CHAIN)			\
{									\
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant ((ADDR), 16)),	\
		  (CHAIN));						\
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant ((ADDR), 20)),	\
		  (FNADDR));						\
}


/* Implicit Calls to Library Routines */

#define TARGET_MEM_FUNCTIONS 1

#define OVERRIDE_OPTIONS  thumb_override_options ()


/* Addressing Modes */

#define HAVE_POST_INCREMENT 1

#define CONSTANT_ADDRESS_P(X)					\
 (GET_CODE (X) == SYMBOL_REF && CONSTANT_POOL_ADDRESS_P (X))

#define MAX_REGS_PER_ADDRESS 2

#ifdef REG_OK_STRICT

#define REG_OK_FOR_BASE_P(X) REGNO_OK_FOR_BASE_P (REGNO (X))
#define REG_OK_FOR_INDEX_P(X) REGNO_OK_FOR_INDEX_P (REGNO (X))

#define REG_MODE_OK_FOR_BASE_P(X,MODE)			\
  REGNO_MODE_OK_FOR_BASE_P (REGNO (X), MODE)

#else /* REG_OK_STRICT */

#define REG_OK_FOR_BASE_P(X)				\
 (REGNO (X) < 8 || REGNO (X) == STACK_POINTER_REGNUM	\
  || (X) == arg_pointer_rtx				\
  || REGNO (X) >= FIRST_PSEUDO_REGISTER)

#define REG_MODE_OK_FOR_BASE_P(X,MODE)			\
 (REGNO (X) < 8						\
  || REGNO (X) >= FIRST_PSEUDO_REGISTER			\
  || (GET_MODE_SIZE (MODE) >= 4				\
      && (REGNO (X) == STACK_POINTER_REGNUM		\
	  || (X) == arg_pointer_rtx)))

#define REG_OK_FOR_INDEX_P(X)				\
 (REGNO (X) < 8						\
  || REGNO (X) >= FIRST_PSEUDO_REGISTER)

#endif /* REG_OK_STRICT */

/* In a REG+REG address, both must be INDEX registers.  */
#define REG_OK_FOR_INDEXED_BASE_P(X) REG_OK_FOR_INDEX_P(X)

#define LEGITIMATE_OFFSET(MODE,VAL)				\
(GET_MODE_SIZE (MODE) == 1 ? ((HOST_WIDE_UINT) (VAL) < 32)	\
 : GET_MODE_SIZE (MODE) == 2 ? ((HOST_WIDE_UINT) (VAL) < 64	\
				&& ((VAL) & 1) == 0)			\
 : ((VAL) >= 0 && ((VAL) + GET_MODE_SIZE (MODE)) <= 128			\
    && ((VAL) & 3) == 0))

/* The AP may be eliminated to either the SP or the FP, so we use the
   least common denominator, e.g. SImode, and offsets from 0 to 64.  */

/* ??? Verify whether the above is the right approach.  */

/* ??? Also, the FP may be eliminated to the SP, so perhaps that
   needs special handling also.  */

/* ??? Look at how the mips16 port solves this problem.  It probably uses
   better ways to solve some of these problems.  */

/* Although it is not incorrect, we don't accept QImode and HImode
   addresses based on the frame pointer or arg pointer until the reload pass starts.
   This is so that eliminating such addresses into stack based ones
   won't produce impossible code.  */
#define GO_IF_LEGITIMATE_ADDRESS(MODE,X,WIN)				\
{									\
  /* ??? Not clear if this is right.  Experiment.  */			\
  if (GET_MODE_SIZE (MODE) < 4						\
      && ! (reload_in_progress || reload_completed)			\
      && (reg_mentioned_p (frame_pointer_rtx, X)			\
	  || reg_mentioned_p (arg_pointer_rtx, X)			\
	  || reg_mentioned_p (virtual_incoming_args_rtx, X)		\
	  || reg_mentioned_p (virtual_outgoing_args_rtx, X)		\
	  || reg_mentioned_p (virtual_stack_dynamic_rtx, X)		\
	  || reg_mentioned_p (virtual_stack_vars_rtx, X)))		\
    ;									\
  /* Accept any base register.  SP only in SImode or larger.  */	\
  else if (GET_CODE (X) == REG && REG_MODE_OK_FOR_BASE_P(X, MODE))	\
    goto WIN;								\
  /* This is PC relative data before MACHINE_DEPENDENT_REORG runs.  */	\
  else if (GET_MODE_SIZE (MODE) >= 4 && CONSTANT_P (X)			\
	   && CONSTANT_POOL_ADDRESS_P (X))				\
    goto WIN;								\
  /* This is PC relative data after MACHINE_DEPENDENT_REORG runs.  */	\
  else if (GET_MODE_SIZE (MODE) >= 4 && reload_completed		\
	   && (GET_CODE (X) == LABEL_REF				\
	       || (GET_CODE (X) == CONST				\
		   && GET_CODE (XEXP (X, 0)) == PLUS			\
		   && GET_CODE (XEXP (XEXP (X, 0), 0)) == LABEL_REF	\
		   && GET_CODE (XEXP (XEXP (X, 0), 1)) == CONST_INT)))	\
    goto WIN;								\
  /* Post-inc indexing only supported for SImode and larger.  */	\
  else if (GET_CODE (X) == POST_INC && GET_MODE_SIZE (MODE) >= 4	\
	   && GET_CODE (XEXP (X, 0)) == REG				\
	   && REG_OK_FOR_INDEX_P (XEXP (X, 0)))				\
    goto WIN;								\
  else if (GET_CODE (X) == PLUS)					\
    {									\
      /* REG+REG address can be any two index registers.  */		\
      /* ??? REG+REG addresses have been completely disabled before	\
	 reload completes, because we do not have enough available	\
	 reload registers.  We only have 3 guaranteed reload registers	\
	 (NONARG_LO_REGS - the frame pointer), but we need at least 4	\
	 to support REG+REG addresses.  We have left them enabled after	\
	 reload completes, in the hope that reload_cse_regs and related	\
	 routines will be able to create them after the fact.  It is	\
	 probably possible to support REG+REG addresses with additional	\
	 reload work, but I do not not have enough time to attempt such	\
	 a change at this time.  */					\
      /* ??? Normally checking the mode here is wrong, since it isn't	\
	 impossible to use REG+REG with DFmode.  However, the movdf	\
	 pattern requires offsettable addresses, and REG+REG is not	\
	 offsettable, so it must be rejected somehow.  Trying to use	\
	 'o' fails, because offsettable_address_p does a QImode check.	\
	 QImode is not valid for stack addresses, and has a smaller	\
	 range for non-stack bases, and this causes valid addresses	\
	 to be rejected.  So we just eliminate REG+REG here by checking	\
	 the mode.  */							\
      /* We also disallow FRAME+REG addressing since we know that FRAME \
	 will be replaced with STACK, and SP relative addressing only   \
	 permits SP+OFFSET.  */						\
      if (GET_MODE_SIZE (MODE) <= 4					\
	  /* ??? See comment above.  */					\
	  && reload_completed						\
	  && GET_CODE (XEXP (X, 0)) == REG				\
	  && GET_CODE (XEXP (X, 1)) == REG				\
	  && XEXP (X, 0) != frame_pointer_rtx				\
	  && XEXP (X, 1) != frame_pointer_rtx				\
	  && XEXP (X, 0) != virtual_stack_vars_rtx			\
	  && XEXP (X, 1) != virtual_stack_vars_rtx			\
	  && REG_OK_FOR_INDEX_P (XEXP (X, 0))				\
	  && REG_OK_FOR_INDEX_P (XEXP (X, 1)))				\
	goto WIN;							\
      /* REG+const has 5-7 bit offset for non-SP registers.  */		\
      else if (GET_CODE (XEXP (X, 0)) == REG				\
	       && (REG_OK_FOR_INDEX_P (XEXP (X, 0))			\
		   || XEXP (X, 0) == arg_pointer_rtx)			\
	       && GET_CODE (XEXP (X, 1)) == CONST_INT			\
	       && LEGITIMATE_OFFSET (MODE, INTVAL (XEXP (X, 1))))	\
	goto WIN;							\
      /* REG+const has 10 bit offset for SP, but only SImode and	\
	 larger is supported.  */					\
      /* ??? Should probably check for DI/DFmode overflow here		\
	 just like GO_IF_LEGITIMATE_OFFSET does.  */			\
      else if (GET_CODE (XEXP (X, 0)) == REG				\
	       && REGNO (XEXP (X, 0)) == STACK_POINTER_REGNUM		\
	       && GET_MODE_SIZE (MODE) >= 4				\
	       && GET_CODE (XEXP (X, 1)) == CONST_INT			\
	       && (HOST_WIDE_UINT) INTVAL (XEXP (X, 1)) < 1024	\
	       && (INTVAL (XEXP (X, 1)) & 3) == 0)			\
	goto WIN;							\
    }									\
}

/* ??? If an HImode FP+large_offset address is converted to an HImode
   SP+large_offset address, then reload won't know how to fix it.  It sees
   only that SP isn't valid for HImode, and so reloads the SP into an index
   register, but the resulting address is still invalid because the offset
   is too big.  We fix it here instead by reloading the entire address.  */
/* We could probably achieve better results by defining PROMOTE_MODE to help
   cope with the variances between the Thumb's signed and unsigned byte and
   halfword load instructions.  */
#define LEGITIMIZE_RELOAD_ADDRESS(X,MODE,OPNUM,TYPE,IND_LEVELS,WIN)	\
{									\
  if (GET_CODE (X) == PLUS						\
      && GET_MODE_SIZE (MODE) < 4					\
      && GET_CODE (XEXP (X, 0)) == REG					\
      && XEXP (X, 0) == stack_pointer_rtx				\
      && GET_CODE (XEXP (X, 1)) == CONST_INT				\
      && ! LEGITIMATE_OFFSET (MODE, INTVAL (XEXP (X, 1))))		\
    {									\
      rtx orig_X = X;							\
      X = copy_rtx (X);							\
      push_reload (orig_X, NULL_RTX, &X, NULL,			\
		   BASE_REG_CLASS,					\
		   Pmode, VOIDmode, 0, 0, OPNUM, TYPE);			\
      goto WIN;								\
    }									\
}
  
#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL)

#define LEGITIMIZE_ADDRESS(X,OLDX,MODE,WIN)

#define LEGITIMATE_CONSTANT_P(X)	\
 (GET_CODE (X) == CONST_INT		\
  || GET_CODE (X) == CONST_DOUBLE	\
  || CONSTANT_ADDRESS_P (X))


/* Condition Code Status */

#define NOTICE_UPDATE_CC(EXP,INSN)			\
{							\
  if (get_attr_conds ((INSN)) != CONDS_UNCHANGED)	\
    CC_STATUS_INIT;					\
}


/* Describing Relative Costs of Operations */

#define SLOW_BYTE_ACCESS 0

#define SLOW_UNALIGNED_ACCESS 1

#define NO_FUNCTION_CSE 1

#define NO_RECURSIVE_FUNCTION_CSE 1

#define REGISTER_MOVE_COST(FROM,TO) \
  (((FROM) == HI_REGS || (TO) == HI_REGS) ? 4 : 2)

#define MEMORY_MOVE_COST(M,CLASS,IN) \
     ((GET_MODE_SIZE(M) < 4 ? 8 : 2 * GET_MODE_SIZE(M)) * (CLASS == LO_REGS ? 1 : 2))

/* This will allow better space optimization when compiling with -O */
#define BRANCH_COST (optimize > 1 ? 1 : 0)

#define RTX_COSTS(X,CODE,OUTER)					\
 case MULT:							\
   if (GET_CODE (XEXP (X, 1)) == CONST_INT)			\
     {								\
       int cycles = 0;						\
       HOST_WIDE_UINT i = INTVAL (XEXP (X, 1));		\
       while (i)						\
	 {							\
	   i >>= 2;						\
	   cycles++;						\
	 }							\
       return COSTS_N_INSNS (2) + cycles;			\
     }								\
   return COSTS_N_INSNS (1) + 16;				\
 case ASHIFT: case ASHIFTRT: case LSHIFTRT: case ROTATERT:	\
 case PLUS: case MINUS: case COMPARE: case NEG: case NOT:	\
   return COSTS_N_INSNS (1);					\
 case SET:							\
   return (COSTS_N_INSNS (1)					\
	   + 4 * ((GET_CODE (SET_SRC (X)) == MEM)		\
		  + GET_CODE (SET_DEST (X)) == MEM))

#define CONST_COSTS(X,CODE,OUTER)				\
 case CONST_INT:						\
   if ((OUTER) == SET)						\
     {								\
       if ((HOST_WIDE_UINT) INTVAL (X) < 256)		\
	 return 0;						\
       if (thumb_shiftable_const (INTVAL (X)))			\
	 return COSTS_N_INSNS (2);				\
       return COSTS_N_INSNS (3);				\
     }								\
   else if (OUTER == PLUS					\
	    && INTVAL (X) < 256 && INTVAL (X) > -256)		\
     return 0;							\
   else if (OUTER == COMPARE					\
	    && (HOST_WIDE_UINT) INTVAL (X) < 256)	\
     return 0;							\
   else if (OUTER == ASHIFT || OUTER == ASHIFTRT		\
	    || OUTER == LSHIFTRT)				\
     return 0;							\
   return COSTS_N_INSNS (2);					\
 case CONST:							\
 case CONST_DOUBLE:						\
 case LABEL_REF:						\
 case SYMBOL_REF:						\
   return COSTS_N_INSNS(3);

#define ADDRESS_COST(X) 					\
  ((GET_CODE (X) == REG 					\
    || (GET_CODE (X) == PLUS && GET_CODE (XEXP (X, 0)) == REG	\
	&& GET_CODE (XEXP (X, 1)) == CONST_INT))		\
   ? 1 : 2)


/* Position Independent Code */

#define PRINT_OPERAND(STREAM,X,CODE) \
  thumb_print_operand((STREAM), (X), (CODE))

#define PRINT_OPERAND_ADDRESS(STREAM,X)				\
{								\
  if (GET_CODE ((X)) == REG)					\
    fprintf ((STREAM), "[%s]", reg_names[REGNO ((X))]);		\
  else if (GET_CODE ((X)) == POST_INC)				\
    fprintf ((STREAM), "%s!", reg_names[REGNO (XEXP (X, 0))]);	\
  else if (GET_CODE ((X)) == PLUS)				\
    {								\
      if (GET_CODE (XEXP ((X), 1)) == CONST_INT)		\
	fprintf ((STREAM), "[%s, #%d]", 			\
		 reg_names[REGNO (XEXP ((X), 0))],		\
		 (int) INTVAL (XEXP ((X), 1)));			\
      else							\
	fprintf ((STREAM), "[%s, %s]",				\
		 reg_names[REGNO (XEXP ((X), 0))],		\
		 reg_names[REGNO (XEXP ((X), 1))]);		\
    }								\
  else								\
    output_addr_const ((STREAM), (X));				\
}

#define PRINT_OPERAND_PUNCT_VALID_P(CODE) ((CODE) == '@' || ((CODE) == '_'))

#define ASM_OUTPUT_REG_PUSH(STREAM,REGNO)			\
  asm_fprintf ((STREAM), "\tpush {%R%s}\n", reg_names[(REGNO)])

#define ASM_OUTPUT_REG_POP(STREAM,REGNO)			\
  fprintf ((STREAM), "\tpop {%R%s}\n", reg_names[(REGNO)])

#define FINAL_PRESCAN_INSN(INSN,OPVEC,NOPERANDS) \
  final_prescan_insn((INSN))

/* Controlling Debugging Information Format */
#define DBX_REGISTER_NUMBER(REGNO) (REGNO)

/* Specific options for DBX Output */

#define DBX_DEBUGGING_INFO 1

#define DEFAULT_GDB_EXTENSIONS 1


/* Cross Compilation and Floating Point */

#define REAL_ARITHMETIC


/* Miscellaneous Parameters */

#define PREDICATE_CODES \
  {"thumb_cmp_operand", {SUBREG, REG, CONST_INT}},

#define CASE_VECTOR_MODE Pmode

#define WORD_REGISTER_OPERATIONS

#define LOAD_EXTEND_OP(MODE) ZERO_EXTEND

#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR

#define EASY_DIV_EXPR TRUNC_DIV_EXPR

#define MOVE_MAX 4

#define TRULY_NOOP_TRUNCATION(OUTPREC,INPREC) 1

#define STORE_FLAG_VALUE 1

#define Pmode SImode

#define FUNCTION_MODE SImode

#define NO_DOLLAR_IN_LABEL 1

#define HAVE_ATEXIT

/* The literal pool needs to reside in the text area due to the
   limited PC addressing range: */
#define MACHINE_DEPENDENT_REORG(INSN) thumb_reorg ((INSN))

#include <stdio.h>

enum machine_mode;

struct rtx_def;
typedef struct rtx_def *rtx;

union tree_node;
typedef union tree_node *tree;

extern int thumb_cmp_operand(rtx, enum machine_mode);
extern void thumb_reorg(rtx first);
extern void thumb_expand_movstrqi(rtx *);
extern void thumb_reload_out_si(rtx);
extern void final_prescan_insn(rtx);
extern int far_jump_used_p();
extern void thumb_function_prologue(FILE *, int);
extern void thumb_expand_prologue();
extern void thumb_function_epilogue(FILE *, int);
extern void thumb_expand_epilogue();
extern char *thumb_unexpanded_epilogue();
extern char *thumb_load_double_from_address();
extern char *output_move_mem_multiple();
extern void thumb_print_operand(FILE *, rtx, int);
extern int thumb_return_in_memory(tree);
extern void thumb_override_options();
extern int arm_valid_machine_decl_attribute(tree, tree, tree, tree);
extern int s_register_operand(rtx, enum machine_mode);
