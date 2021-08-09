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
	stmfd	sp!, {r4, r5}
	mov	ip, r0
	add	r5, r0, #64
	b	.L2
.L7:
	add	r0, r0, r4
	ldmfd	sp!, {r4, r5}
	bx	lr
.L2:
	ldrb	r2, [ip, #6]	@ zero_extendqisi2
	ldrb	r3, [r1, #6]	@ zero_extendqisi2
#APP
@ 16 "sad_hw.c" 1
	SAD r2, r3, r4
@ 0 "" 2
	ldrb	r2, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [r1, #7]	@ zero_extendqisi2
#APP
@ 21 "sad_hw.c" 1
	SAD r2, r3, r0
@ 0 "" 2
	add	ip, ip, #8
	add	r1, r1, #8
	cmp	ip, r5
	bne	.L2
	b	.L7
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
