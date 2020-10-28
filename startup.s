
	.cpu cortex-m0plus
	.syntax unified
	.thumb
	.fpu softvfp

	.global _vectors, _start

	.section .vectors
	.align 2

	.type _vectors, %object
_vectors:
	.long _stack_top
	.long _start

	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0

	.size _vectors, . - _vectors

	.text
	.align 1

	.type _start, %function
_start:
	b main

	.end

// vi:noai:noexpandtab:ts=8:sw=8
