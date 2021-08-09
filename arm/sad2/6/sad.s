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
	stmfd	sp!, {r4, r5, r6, r7, r8}
	mov	r6, r0
	mov	r7, r1
	mov	r5, #0
	add	r8, r0, #64
.L18:
	ldrb	r0, [r6, #0]	@ zero_extendqisi2
	ldrb	r3, [r7, #0]	@ zero_extendqisi2
	ldrb	ip, [r6, #1]	@ zero_extendqisi2
	ldrb	r2, [r7, #1]	@ zero_extendqisi2
	rsb	r3, r0, r3
	cmp	r3, #0
	rsb	r2, ip, r2
	ldrb	r4, [r6, #2]	@ zero_extendqisi2
	ldrb	r1, [r7, #2]	@ zero_extendqisi2
	rsblt	r3, r3, r5
	addge	r3, r5, r3
	ldrb	r0, [r7, #3]	@ zero_extendqisi2
	cmp	r2, #0
	ldrb	r5, [r6, #3]	@ zero_extendqisi2
	rsblt	r3, r2, r3
	addge	r3, r3, r2
	rsb	r1, r4, r1
	ldrb	r2, [r7, #4]	@ zero_extendqisi2
	ldrb	r4, [r6, #4]	@ zero_extendqisi2
	rsb	r0, r5, r0
	cmp	r1, #0
	rsblt	r3, r1, r3
	addge	r3, r3, r1
	rsb	r2, r4, r2
	ldrb	r5, [r6, #5]	@ zero_extendqisi2
	cmp	r0, #0
	ldrb	ip, [r7, #5]	@ zero_extendqisi2
	rsblt	r3, r0, r3
	addge	r3, r3, r0
	ldrb	r1, [r7, #6]	@ zero_extendqisi2
	cmp	r2, #0
	ldrb	r4, [r6, #6]	@ zero_extendqisi2
	rsblt	r3, r2, r3
	addge	r3, r3, r2
	rsb	ip, r5, ip
	ldrb	r2, [r7, #7]	@ zero_extendqisi2
	ldrb	r0, [r6, #7]	@ zero_extendqisi2
	cmp	ip, #0
	rsb	r1, r4, r1
	rsblt	r3, ip, r3
	addge	r3, r3, ip
	rsb	r2, r0, r2
	cmp	r1, #0
	rsblt	r3, r1, r3
	addge	r3, r3, r1
	add	r6, r6, #8
	cmp	r2, #0
	rsblt	r5, r2, r3
	addge	r5, r2, r3
	cmp	r6, r8
	add	r7, r7, #8
	bne	.L18
	mov	r0, r5
	ldmfd	sp!, {r4, r5, r6, r7, r8}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
