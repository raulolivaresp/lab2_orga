j main

factorial:
beq $a0, $zero, condicionBorde
addi $sp, $sp, -8
sw $ra, 0($sp)
sw $a0, 4($sp)
addi $a0, $a0, -1
add $t0, $t0, $a0
add $t1, $t0, $a0
jal factorial
lw $ra, 0($sp)
lw $a0, 4($sp)
mul $v0, $v0, $a0
addi $sp, $sp, 8
jr $ra
condicionBorde:
addi $v0, $zero, 1
lw $ra, 0($sp)
lw $a0, 4($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
jr $ra

main:
addi $a0, $zero, 6
jal factorial
add $s0, $zero, $v0