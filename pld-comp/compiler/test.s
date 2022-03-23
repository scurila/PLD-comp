.section	__TEXT,__text,regular,pure_instructions
.build_version macos, 12, 0	sdk_version 12, 3
.globl	_main                           ; -- Begin function main
.p2align	2
_main:                                  ; @main
.cfi_startproc
; %bb.0:
sub	sp, sp, #100
.cfi_def_cfa_offset 100
.L0:
; -- ldconst 
mov w8, #2
str w8, [sp, #4]
; -- ldconst 
mov w8, #8
str w8, [sp, #8]
; -- pushvar 
mov w8, [sp, #4]
push {w8}
; -- pushvar 
mov w8, [sp, #4]
push {w8}
; -- mul 
pop {w8}
pop {w9}
mul w9, w9, w8
push {w9}
; -- pushvar 
mov w8, [sp, #8]
push {w8}
; -- pushvar 
mov w8, [sp, #8]
push {w8}
; -- mul 
pop {w8}
pop {w9}
mul w9, w9, w8
push {w9}
; -- add 
pop {w8}
pop {w9}
add w8, w8, w9
push {w8}
; -- pushconst 
mov w8 #1
; -- add 
pop {w8}
pop {w9}
add w8, w8, w9
push {w8}
; -- ldconst 
pop {w8}
mov [sp, #12], w8
; -- pushvar 
mov w8, [sp, #12]
push {w8}
pop {w0}
add sp, sp, #100
ret
.cfi_endproc
.subsections_via_symbols
