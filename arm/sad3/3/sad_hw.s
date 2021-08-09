	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"sad_hw.c"
	.text
	.align	2
	.global	calculate_sad
	.type	calculate_sad, %function
calculate_sad:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #44
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r1, #0
	str	r1, [fp, #-40]
	mov	r2, #0
	mov	r3, #0
	mov	r3, #0
	strb	r3, [fp, #-6]
	mov	r3, #0
	strb	r3, [fp, #-5]
	mov	r1, #0
	str	r1, [fp, #-24]
	b	.L2
.L5:
	mov	r2, #0
	str	r2, [fp, #-28]
	b	.L3
.L4:
	mov	r3, #0
	str	r3, [fp, #-36]
	ldr	r1, [fp, #-24]
	mov	r2, r1, asl #3
	ldr	r3, [fp, #-16]
	add	r2, r3, r2
	ldr	r3, [fp, #-28]
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r3, r3, asl #24
	ldr	r2, [fp, #-36]
	orr	r2, r2, r3
	str	r2, [fp, #-36]
	ldr	r3, [fp, #-24]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-16]
	add	r2, r3, r2
	ldr	r1, [fp, #-28]
	add	r3, r1, #1
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	ldr	r2, [fp, #-36]
	orr	r2, r2, r3
	str	r2, [fp, #-36]
	ldr	r3, [fp, #-24]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-16]
	add	r2, r3, r2
	ldr	r1, [fp, #-28]
	add	r3, r1, #2
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	ldr	r2, [fp, #-36]
	orr	r2, r2, r3
	str	r2, [fp, #-36]
	ldr	r3, [fp, #-24]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-16]
	add	r2, r3, r2
	ldr	r1, [fp, #-28]
	add	r3, r1, #3
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	ldr	r2, [fp, #-36]
	orr	r2, r2, r3
	str	r2, [fp, #-36]
	mov	r3, #0
	str	r3, [fp, #-32]
	ldr	r1, [fp, #-24]
	mov	r2, r1, asl #3
	ldr	r3, [fp, #-20]
	add	r2, r3, r2
	ldr	r3, [fp, #-28]
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r3, r3, asl #24
	ldr	r2, [fp, #-32]
	orr	r2, r2, r3
	str	r2, [fp, #-32]
	ldr	r3, [fp, #-24]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-20]
	add	r2, r3, r2
	ldr	r1, [fp, #-28]
	add	r3, r1, #1
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	ldr	r2, [fp, #-32]
	orr	r2, r2, r3
	str	r2, [fp, #-32]
	ldr	r3, [fp, #-24]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-20]
	add	r2, r3, r2
	ldr	r1, [fp, #-28]
	add	r3, r1, #2
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	ldr	r2, [fp, #-32]
	orr	r2, r2, r3
	str	r2, [fp, #-32]
	ldr	r3, [fp, #-24]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-20]
	add	r2, r3, r2
	ldr	r1, [fp, #-28]
	add	r3, r1, #3
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	ldr	r2, [fp, #-32]
	orr	r2, r2, r3
	str	r2, [fp, #-32]
	ldr	r3, [fp, #-36]
	ldr	r1, [fp, #-32]
#APP
@ 35 "sad_hw.c" 1
	SAD r3, r1, r3
@ 0 "" 2
	str	r3, [fp, #-40]
	ldr	r2, [fp, #-28]
	add	r2, r2, #4
	str	r2, [fp, #-28]
.L3:
	ldr	r3, [fp, #-28]
	cmp	r3, #7
	bls	.L4
	ldr	r1, [fp, #-24]
	add	r1, r1, #1
	str	r1, [fp, #-24]
.L2:
	ldr	r2, [fp, #-24]
	cmp	r2, #7
	bls	.L5
	ldr	r3, [fp, #-40]
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
