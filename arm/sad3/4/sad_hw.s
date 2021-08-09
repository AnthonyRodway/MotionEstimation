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
	stmfd	sp!, {r4, r5, r6}
	mov	r6, r1
	mov	r3, r0
	mov	r4, #0
	b	.L2
.L3:
	ldrb	r3, [ip, #0]	@ zero_extendqisi2
	ldrb	r2, [ip, #1]	@ zero_extendqisi2
	mov	r2, r2, asl #16
	orr	r2, r2, r3, asl #24
	ldrb	r3, [ip, #3]	@ zero_extendqisi2
	orr	r2, r2, r3
	ldrb	r1, [r0, #0]	@ zero_extendqisi2
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, r1, asl #24
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	orr	r3, r3, r1
	ldrb	r1, [ip, #2]	@ zero_extendqisi2
	orr	r2, r2, r1, asl #8
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	orr	r3, r3, r1, asl #8
#APP
@ 35 "sad_hw.c" 1
	SAD r2, r3, r2
@ 0 "" 2
	add	ip, ip, #4
	add	r0, r0, #4
	mov	r3, r5
	cmp	r5, ip
	bne	.L3
	add	r4, r4, #8
	cmp	r4, #64
	bne	.L2
	mov	r0, r2
	ldmfd	sp!, {r4, r5, r6}
	bx	lr
.L2:
	add	r0, r6, r4
	mov	ip, r3
	add	r5, r3, #8
	b	.L3
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
