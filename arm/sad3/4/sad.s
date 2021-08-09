	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 1
	.eabi_attribute 18, 4
	.file	"sad.c"
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
	mov	r3, r0
	mov	r5, #0
	mov	r7, r5
	mov	sl, #24
	b	.L2
.L7:
	ldrb	r2, [r1, #0]	@ zero_extendqisi2
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, r2, asl #24
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	orr	r3, r3, r2
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	orr	r6, r3, r2, asl #8
	ldrb	r2, [r0, #0]	@ zero_extendqisi2
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, r2, asl #24
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	orr	r3, r3, r2
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	orr	r4, r3, r2, asl #8
	cmp	r6, r4
	beq	.L3
	mov	ip, sl
.L6:
	mov	r2, r4, lsr ip
	and	r2, r2, #255
	mov	r3, r6, lsr ip
	and	r3, r3, #255
	subs	r2, r2, r3
	rsbmi	r5, r2, r5
	addpl	r5, r5, r2
	sub	ip, ip, #8
	cmn	ip, #8
	bne	.L6
.L3:
	add	r1, r1, #4
	add	r0, r0, #4
	mov	r3, r8
	cmp	r8, r1
	bne	.L7
	add	r7, r7, #8
	cmp	r7, #64
	bne	.L2
	mov	r0, r5
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl}
	bx	lr
.L2:
	add	r0, r9, r7
	mov	r1, r3
	add	r8, r3, #8
	b	.L7
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
