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
	add	ip, r0, #64
.L2:
	ldrb	r2, [r0, #7]	@ zero_extendqisi2
	add	r0, r0, #8
	cmp	r0, ip
	ldrb	r3, [r1, #7]	@ zero_extendqisi2
#APP
@ 15 "sad_hw.c" 1
	SAD r2, r3, r3
@ 0 "" 2
	add	r1, r1, #8
	bne	.L2
	mov	r0, r3
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
