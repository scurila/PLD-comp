.section	__TEXT,__text,regular,pure_instructions
.build_version macos, 12, 0	sdk_version 12, 3
.globl	_main                           ; -- Begin function main
.p2align	2
_main:                                  ; @main
.cfi_startproc
; %bb.0:
sub	sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
.cfi_def_cfa_offset 32
.L0:
; -- ldconst 
mov w8, #17
str w8, [x29, #-16]
; -- copy
ldr w8, [x29, #-16]
str w8, [x29, #-20]
; -- pushvar 
ldr w3, [x29, #-20]
str w3, [sp, #-4]!
ldp x29, x30, [sp, #16]
ldr w0, [sp], #4
add sp, sp, #32
ret
.cfi_endproc
.subsections_via_symbols
