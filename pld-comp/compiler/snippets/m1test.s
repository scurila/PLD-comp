.section	__TEXT,__text,regular,pure_instructions
.build_version macos, 12, 0	sdk_version 12, 3
.globl	_main                           ; -- Begin function main
.p2align	3
_main:                                  ; @main
.cfi_startproc
; %bb.0:
sub	sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
.cfi_def_cfa_offset 48
.L0:
; -- ldconst 
mov x8, #2
str x8, [x29, #-8]
; -- pushvar 
ldr x3, [x29, #-8]
str x3, [sp, #-16]!
; -- pushconst 
mov x8, #2
str x8, [sp, #-16]!
; -- add 
ldr x8, [sp], #16
ldr x9, [sp], #16
add x8, x8, x9
str x8, [sp, #-16]!
; -- ldconst 
ldr x8, [sp], #16
str x8, [x29, #-8]
; -- pushvar 
ldr x3, [x29, #-8]
str x3, [sp, #-16]!
; -- pushconst 
mov x8, #2
str x8, [sp, #-16]!
; -- pushconst 
mov x8, #5
str x8, [sp, #-16]!
; -- mul 
ldr x8, [sp], #16
ldr x9, [sp], #16
mul x9, x9, x8
str x9, [sp, #-16]!
; -- add 
ldr x8, [sp], #16
ldr x9, [sp], #16
add x8, x8, x9
str x8, [sp, #-16]!
; -- ldconst 
ldr x8, [sp], #16
str x8, [x29, #-16]
; -- pushvar 
ldr x3, [x29, #-16]
str x3, [sp, #-16]!
ldr x0, [sp], #16
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.cfi_endproc
.subsections_via_symbols
