	.include "asm/macros.inc"
	.include "constants/constants.inc"
	.text
	.syntax unified
	.align 2, 0
	arm_func_start NESPipelineTest_Internal
NESPipelineTest_Internal:
	mov	r2, lr
	mov	r1, #0
	add	lr, pc, #8
	ldr	r0, [pc, #-16]
	str	r0, [lr]
	mov	r1, #0xFF
	mov	r1, #0xFF
	ldr	r0, =gEmulatorCheck
	strb	r1, [r0]
	bx	r2
	.pool
	arm_func_end NESPipelineTest_Internal
	.global NESPipelineTest_Internal_End
NESPipelineTest_Internal_End:
