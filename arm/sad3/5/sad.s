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
	mov	r7, #0
	mov	r9, r1
	mov	r8, r7
.L2:
	mov	r5, r0
	add	r6, r9, r8
	add	sl, r0, #8
.L7:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	ldrb	r2, [r6, #1]	@ zero_extendqisi2
	ldrb	r1, [r5, #0]	@ zero_extendqisi2
	ldrb	r0, [r6, #0]	@ zero_extendqisi2
	ldrb	ip, [r5, #3]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	mov	r2, r2, asl #16
	ldrb	r4, [r6, #3]	@ zero_extendqisi2
	orr	r3, r3, r1, asl #24
	orr	r2, r2, r0, asl #24
	ldrb	r1, [r5, #2]	@ zero_extendqisi2
	ldrb	r0, [r6, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	orr	r2, r2, r4
	orr	ip, r3, r1, asl #8
	orr	r0, r2, r0, asl #8
	cmp	ip, r0
	beq	.L3
	mov	r1, #24
.L6:
	mov	r2, r0, lsr r1
	mov	r3, ip, lsr r1
	and	r2, r2, #255
	and	r3, r3, #255
	subs	r2, r2, r3
	sub	r1, r1, #8
	rsbmi	r7, r2, r7
	addpl	r7, r7, r2
	cmn	r1, #8
	bne	.L6
.L3:
	add	r5, r5, #4
	cmp	sl, r5
	add	r6, r6, #4
	bne	.L7
	add	r8, r8, #8
	cmp	r8, #64
	movne	r0, sl
	bne	.L2
.L8:
	mov	r0, r7
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
