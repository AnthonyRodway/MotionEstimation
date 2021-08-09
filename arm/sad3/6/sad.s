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
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	mov	sl, #0
	sub	sp, sp, #8
	str	r1, [sp, #4]
	mov	r9, sl
	mov	r3, r1
	b	.L2
.L17:
	ldr	r3, [sp, #4]
	mov	r0, fp
.L2:
	mov	r7, r0
	add	r8, r3, r9
	add	fp, r0, #8
.L12:
	ldrb	r0, [r7, #1]	@ zero_extendqisi2
	ldrb	r3, [r7, #0]	@ zero_extendqisi2
	ldrb	r1, [r8, #1]	@ zero_extendqisi2
	ldrb	r2, [r8, #0]	@ zero_extendqisi2
	ldrb	ip, [r7, #3]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	ldrb	r4, [r8, #3]	@ zero_extendqisi2
	orr	r0, r0, r3, asl #24
	mov	r1, r1, asl #16
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	ldrb	r5, [r8, #2]	@ zero_extendqisi2
	orr	r1, r1, r2, asl #24
	orr	r0, r0, ip
	orr	r0, r0, r3, asl #8
	orr	r1, r1, r4
	orr	r1, r1, r5, asl #8
	mov	ip, r0, lsr #16
	mov	r2, r0, lsr #24
	and	ip, ip, #255
	mov	r3, r1, asl #8
	mov	r4, r0, lsr #8
	rsb	r5, ip, r3, lsr #24
	and	r4, r4, #255
	rsb	r6, r2, r1, lsr #24
	and	ip, r1, #255
	mov	r2, r1, asl #16
	and	r3, r0, #255
	cmp	r0, r1
	add	r7, r7, #4
	add	r8, r8, #4
	rsb	r2, r4, r2, lsr #24
	rsb	ip, r3, ip
	beq	.L3
	cmp	r6, #0
	rsblt	r3, r6, sl
	addge	r3, sl, r6
	cmp	r5, #0
	rsblt	r3, r5, r3
	addge	r3, r3, r5
	cmp	r2, #0
	rsblt	r3, r2, r3
	addge	r3, r3, r2
	cmp	ip, #0
	rsblt	sl, ip, r3
	addge	sl, ip, r3
.L3:
	cmp	fp, r7
	bne	.L12
	add	r9, r9, #8
	cmp	r9, #64
	bne	.L17
	mov	r0, sl
	add	sp, sp, #8
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
