	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"sad_hw.c"
	.text
	.align	2
	.global	calculate_sad
	.type	calculate_sad, %function
calculate_sad:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #44
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	mov	r3, #0
	str	r3, [fp, #-20]
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L5:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L3
.L4:
	ldr	r3, [fp, #-8]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-40]
	add	r2, r3, r2
	ldr	r3, [fp, #-12]
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-8]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r2, r3, r2
	ldr	r3, [fp, #-12]
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	str	r3, [fp, #-28]
	ldr	r2, [fp, #-36]
	ldr	r3, [fp, #-28]
#APP
@ 16 "sad_hw.c" 1
	SAD r2, r3, r3
@ 0 "" 2
	str	r3, [fp, #-20]
	ldr	r3, [fp, #-8]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-40]
	add	r2, r3, r2
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-8]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r2, r3, r2
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	str	r3, [fp, #-24]
	ldr	r2, [fp, #-32]
	ldr	r3, [fp, #-24]
#APP
@ 21 "sad_hw.c" 1
	SAD r2, r3, r3
@ 0 "" 2
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-12]
	add	r3, r3, #2
	str	r3, [fp, #-12]
.L3:
	ldr	r3, [fp, #-12]
	cmp	r3, #7
	ble	.L4
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r3, [fp, #-8]
	cmp	r3, #7
	ble	.L5
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-16]
	add	r3, r2, r3
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	calculate_sad, .-calculate_sad
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
