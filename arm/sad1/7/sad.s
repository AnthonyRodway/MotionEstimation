	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 4
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
	mov	ip, #0
	stmfd	sp!, {r4, r5, r6, r7}
	mov	r7, r0
	mov	r6, r1
	mov	r4, ip
	mov	r5, ip
	b	.L2
.L7:
	ldrb	r3, [r0, #0]	@ zero_extendqisi2
	ldrb	r2, [r1, #0]	@ zero_extendqisi2
	subs	r2, r2, r3
	rsbmi	ip, r2, ip
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	addpl	ip, ip, r2
	ldrb	r2, [r1, #1]	@ zero_extendqisi2
	add	r1, r1, #2
	subs	r2, r2, r3
	add	r3, r6, #8
	rsbmi	r4, r2, r4
	addpl	r4, r4, r2
	cmp	r1, r3
	add	r0, r0, #2
	bne	.L7
	add	r5, r5, #8
	cmp	r5, #64
	beq	.L8
	mov	r6, r1
.L2:
	add	r0, r7, r5
	mov	r1, r6
	b	.L7
.L8:
	add	r0, ip, r4
	ldmfd	sp!, {r4, r5, r6, r7}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
