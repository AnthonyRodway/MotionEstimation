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
	stmfd	sp!, {r4, r5, r6, r7, r8}
	mov	r7, r1
	mov	r6, r0
	mov	r5, #0
	mov	r8, r5
	b	.L2
.L3:
	ldrb	r2, [r4, ip]	@ zero_extendqisi2
	ldrb	r3, [r1, ip]	@ zero_extendqisi2
#APP
@ 16 "sad_hw.c" 1
	SAD r2, r3, r0
@ 0 "" 2
	add	ip, ip, #1
	cmp	ip, #8
	bne	.L3
	add	r6, r6, #8
	add	r5, r5, #8
	cmp	r5, #64
	bne	.L2
	ldmfd	sp!, {r4, r5, r6, r7, r8}
	bx	lr
.L2:
	mov	r4, r6
	add	r1, r7, r5
	mov	ip, r8
	b	.L3
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
