	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 12, 3
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	mov	w8, #17
	stur	w8, [x29, #-8]
	ldur	w8, [x29, #-8]
	stur	w8, [x29, #-12]
	mov	w0, #1
	mov	w1, #2
	mov	w2, #3
	mov	w3, #4
	mov	w4, #56
	mov	w5, #7
	mov	w6, #8
	mov	w7, #9
	mov	x9, sp
	mov	w8, #10
	str	w8, [x9]
	mov	w8, #11
	str	w8, [x9, #4]
	bl	_fun
	ldur	w0, [x29, #-12]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
