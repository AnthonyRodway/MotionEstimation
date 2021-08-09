	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 18, 4
	.file	"sad_hw.c"
	.text
	.align	2
	.global	calculate_sad
	.type	calculate_sad, %function
calculate_sad:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl}
	mov	r9, r1
	mov	r8, #0
	b	.L2
.L8:
	mov	r0, r6
.L2:
	mov	r6, r0
	add	r7, r9, r8
	add	sl, r0, #8
.L3:
	ldrb	r2, [r6, #1]	@ zero_extendqisi2
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	ldrb	r1, [r6, #0]	@ zero_extendqisi2
	ldrb	r0, [r7, #0]	@ zero_extendqisi2
	ldrb	r4, [r6, #3]	@ zero_extendqisi2
	ldrb	r5, [r7, #3]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	mov	r3, r3, asl #16
	orr	r2, r2, r1, asl #24
	orr	r3, r3, r0, asl #24
	ldrb	ip, [r6, #2]	@ zero_extendqisi2
	ldrb	r1, [r7, #2]	@ zero_extendqisi2
	add	r6, r6, #4
	orr	r2, r2, r4
	orr	r3, r3, r5
	cmp	r6, sl
	orr	r2, r2, ip, asl #8
	orr	r3, r3, r1, asl #8
	add	r7, r7, #4
#APP
@ 35 "sad_hw.c" 1
	SAD r2, r3, r0
@ 0 "" 2
	bne	.L3
	add	r8, r8, #8
	cmp	r8, #64
	bne	.L8
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
