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
	stmfd	sp!, {r4, r5, r6}
	mov	r5, #0
	mov	ip, r0
	mov	r4, r5
	add	r6, r1, #64
	b	.L2
.L3:
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #7]	@ zero_extendqisi2
	add	r1, r1, #8
	subs	r2, r2, r3
	rsbmi	r4, r2, r4
	addpl	r4, r2, r4
	cmp	r1, r6
	add	ip, ip, #8
	beq	.L6
.L2:
	ldrb	r2, [r1, #0]	@ zero_extendqisi2
	ldrb	r3, [ip, #0]	@ zero_extendqisi2
	subs	r0, r2, r3
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	ldrb	r2, [r1, #1]	@ zero_extendqisi2
	addpl	r5, r5, r0
	rsbmi	r5, r0, r5
	subs	r2, r2, r3
	addpl	r4, r4, r2
	rsbmi	r4, r2, r4
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	subs	r0, r2, r3
	ldrb	r3, [ip, #3]	@ zero_extendqisi2
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	addpl	r5, r5, r0
	rsbmi	r5, r0, r5
	subs	r2, r2, r3
	addpl	r4, r4, r2
	rsbmi	r4, r2, r4
	ldrb	r3, [ip, #4]	@ zero_extendqisi2
	ldrb	r2, [r1, #4]	@ zero_extendqisi2
	subs	r0, r2, r3
	ldrb	r3, [ip, #5]	@ zero_extendqisi2
	ldrb	r2, [r1, #5]	@ zero_extendqisi2
	addpl	r5, r5, r0
	rsbmi	r5, r0, r5
	subs	r2, r2, r3
	addpl	r4, r4, r2
	rsbmi	r4, r2, r4
	ldrb	r3, [ip, #6]	@ zero_extendqisi2
	ldrb	r2, [r1, #6]	@ zero_extendqisi2
	subs	r0, r2, r3
	addpl	r5, r0, r5
	rsbmi	r5, r0, r5
	b	.L3
.L6:
	add	r0, r5, r4
	ldmfd	sp!, {r4, r5, r6}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
