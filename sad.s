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
        .file   "test.c"
        .text
        .align  2
        .global calculate_sad
        .type   calculate_sad, %function
calculate_sad:
        @ Function supports interworking.
        @ args = 8, pretend = 0, frame = 32
        @ frame_needed = 1, uses_anonymous_args = 0
        @ link register save eliminated.
        str     fp, [sp, #-4]!
        add     fp, sp, #0
        sub     sp, sp, #36
        str     r0, [fp, #-24]
        str     r1, [fp, #-28]
        str     r2, [fp, #-32]
        str     r3, [fp, #-36]
        mov     r3, #0
        str     r3, [fp, #-16]
        mov     r3, #0
        str     r3, [fp, #-12]
        b       .L2
.L7:
        mov     r3, #0
        str     r3, [fp, #-8]
        b       .L3
.L6:
        ldr     r2, [fp, #-32]
        ldr     r3, [fp, #-12]
        add     r3, r2, r3
        mov     r2, r3, asl #2
        ldr     r3, [fp, #-28]
        add     r3, r3, r2
        ldr     r1, [r3, #0]
        ldr     r2, [fp, #-36]
        ldr     r3, [fp, #-8]
        add     r3, r2, r3
        add     r3, r1, r3
        ldrb    r3, [r3, #0]    @ zero_extendqisi2
        mov     r0, r3
        ldr     r2, [fp, #-32]
        ldr     r3, [fp, #4]
        add     r2, r2, r3
        ldr     r3, [fp, #-12]
        add     r3, r2, r3
        mov     r2, r3, asl #2
        ldr     r3, [fp, #-24]
        add     r3, r3, r2
        ldr     r1, [r3, #0]
        ldr     r2, [fp, #-36]
        ldr     r3, [fp, #8]
        add     r2, r2, r3
        ldr     r3, [fp, #-8]
        add     r3, r2, r3
        add     r3, r1, r3
        ldrb    r3, [r3, #0]    @ zero_extendqisi2
        rsb     r3, r3, r0
        str     r3, [fp, #-20]
        ldr     r3, [fp, #-20]
        cmp     r3, #0
        bge     .L4
        ldr     r3, [fp, #-16]
        ldr     r2, [fp, #-20]
        rsb     r3, r2, r3
        str     r3, [fp, #-16]
        b       .L5
.L4:
        ldr     r3, [fp, #-16]
        ldr     r2, [fp, #-20]
        add     r3, r3, r2
        str     r3, [fp, #-16]
.L5:
        ldr     r3, [fp, #-8]
        add     r3, r3, #1
        str     r3, [fp, #-8]
.L3:
        ldr     r3, [fp, #-8]
        cmp     r3, #7
        ble     .L6
        ldr     r3, [fp, #-12]
        add     r3, r3, #1
        str     r3, [fp, #-12]
.L2:
        ldr     r3, [fp, #-12]
        cmp     r3, #7
        ble     .L7
        ldr     r3, [fp, #-16]
        mov     r0, r3
        add     sp, fp, #0
        ldmfd   sp!, {fp}
        bx      lr
        .size   calculate_sad, .-calculate_sad
        .ident  "GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
        .section        .note.GNU-stack,"",%progbits