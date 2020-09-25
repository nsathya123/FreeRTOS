/*
/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  link.ld
 * Created date			        :   
 * Brief Description of file    :   linker file
 * Name of Author    	        :  Sathya Narayanan N & Abhinav ramnath
 * Email ID                     :  sathya281@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ***************************************************************************/
*/

#include "platform.h"

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/*----------------------------------------------------------------------*/
/* Sections                                                             */
/*----------------------------------------------------------------------*/

SECTIONS
{

  /* text: test code section */
  . = TCM_MEM_START;
  .text.init : { *(.text.init) }

  .tohost ALIGN(0x1000) : { *(.tohost) }

  .text : { *(.text) }

  .rodata : {
       __rodata_start = .;
       *(.rodata)
       *(.rodata.*)
       *(.gnu.linkonce.r.*)
       __rodata_end = .;
	} 

  .sdata : {
    __global_pointer$ = . + 0x800;
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }

  /* bss segment */
  .sbss : {
	   __sbss_start = .;
	   *(.sbss)
	   *(.sbss.*)
	   *(.gnu.linkonce.sb.*)
	   __sbss_end = .;
	}

  
	
/* data segment */
  .data : {
	   . = ALIGN(4);
	   __data_start = .;
	   *(.data)
	   *(.data.*)
	   *(.gnu.linkonce.d.*)
	   __data_end = .;
	}


  .bss : {
       . = ALIGN(4);
       __bss_start = .;
       *(.bss)
       *(.bss.*)
       *(.gnu.linkonce.b.*)
       *(COMMON)
       . = ALIGN(4);
       __bss_end = .;
    }


  /* thread-local data segment */
  .tdata :
  {
    _tls_data = .;
    *(.tdata.begin)
    *(.tdata)
    *(.tdata.end)
    _tls_end = .;
  }
  .tbss :
  {
    *(.tbss)
    *(.tbss.end)
  }

  . = ALIGN(4);
  _end = .;
  . = TCM_MEM_START + TCM_MEM_SIZE - 4;
   /* 0x8000fffc is for 128kB memory. If you change memory size set it to ( Total Memory Size - 4 Bytes). for example if its 100000 set it to ffffc */
  _free_space = . - _end;
  _STACK_SIZE = (_free_space * STACK_PERCENTAGE) / 100 ;
   /*Splits the available space into 2. 1 half takes up the heap and the bottom half takes up the stack*/
  _HEAP_SIZE = _free_space - _STACK_SIZE;
   
    .stack : {
       _stack_end = .;
       __stack_pointer$ = .;	
       _stack = .  - _STACK_SIZE;
    }
   . = _stack;
   .heap : {
       _heap = . - _HEAP_SIZE;
       _heap_end = .;
    }


  /* End of uninitalized data segement */


  
}




