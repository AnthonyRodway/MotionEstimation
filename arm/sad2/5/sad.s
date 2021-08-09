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
	mov	r4, #0
	mov	r6, r1
	mov	r5, r4
.L2:
	add	r1, r6, r5
	mov	ip, #0
.L5:
	ldrb	r2, [r1, ip]	@ zero_extendqisi2
	ldrb	r3, [r0, ip]	@ zero_extendqisi2
	add	ip, ip, #1
	subs	r2, r2, r3
	rsbmi	r4, r2, r4
	addpl	r4, r4, r2
	cmp	ip, #8
	bne	.L5
	add	r5, r5, #8
	cmp	r5, #64
	add	r0, r0, #8
	bne	.L2
	mov	r0, r4
	ldmfd	sp!, {r4, r5, r6}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
