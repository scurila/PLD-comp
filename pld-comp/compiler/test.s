.text
.globl main
main: 
  pushq %rbp
  movq %rsp, %rbp
  movq %rsp, %rax
  subq $12, %rax
  movq %rax, %rsp
.L0:
  movl $0x3, -12(%rbp)
  movl $0x4, -8(%rbp)
  movl -12(%rbp), %eax
  pushq %rax
  movl -8(%rbp), %eax
  pushq %rax
# divide
  popq %rbx
  popq %rax
  cdq
  idivq %rbx
  pushq %rax
  popq %rax
  movl %eax, -4(%rbp)
  movl -4(%rbp), %eax
  pushq %rax
  popq %rax
  movq %rsp, %rbx
  addq $12, %rbx
  movq %rbx, %rsp
  popq %rbp
  ret
