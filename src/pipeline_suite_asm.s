	.include "asm/macros.inc"
	.include "constants/constants.inc"
	.text
	.syntax unified

	thumb_func_start DoTest_Arm
DoTest_Arm:
	push	{r3}
	push	{r4, r7, lr}
	mov	r7, sp
	adds	r4, r2, #0
	subs	r3, r1, r0
	mov	r2, sp
	subs	r2, r2, r3
	mov	sp, r2
_DoTest_Arm_loop:
	ldmia	r0!, {r3}
	stmia	r2!, {r3}
	cmp	r0, r1
	bcc	_DoTest_Arm_loop
	adds	r0, r7, #0
	adds	r0, r0, #0xC
	mov	r2, sp
	bl	_call_via_r2
	movs	r1, #1
	cmp	r0, r4
	beq	_DoTest_Arm_okay
	movs	r1, #0
_DoTest_Arm_okay:
	adds	r0, r1, #0
	mov	sp, r7
	pop	{r4, r7}
	pop	{r3}
	add	sp, sp, #0x4
	bx	r3
	thumb_func_end DoTest_Arm

	arm_func_start NESPipelineTest_Internal
NESPipelineTest_Internal:
	mov	r1, lr
	mov	r0, #0
	add	lr, pc, #8
	ldr	r0, [pc, #-16]
	str	r0, [lr]
	mov	r0, #0xFF
	mov	r0, #0xFF
	bx	r1
	.pool
	arm_func_end NESPipelineTest_Internal
	.global NESPipelineTest_Internal_End
NESPipelineTest_Internal_End:

	arm_func_start TimerPrescalerTest
TimerPrescalerTest:
	stmda sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
	@ Load from va_list
	ldr r1, [r0, #4]
	ldr r0, [r0]

	mov r2, #0x400
	mov r4, r0
	mov r5, #0
	str r5, [r4] @ Reset
	str r1, [r4] @ Start
_TimerPrescaler_loop:
	subs r2, r2, #1
	bne _TimerPrescaler_loop
	mov r0, r0
	mov r0, r0
	ldrh r0, [r4]
	str r5, [r4]
	ldmib sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	bx lr
	arm_func_end TimerPrescalerTest
	.global TimerPrescalerTest_End
TimerPrescalerTest_End:

	thumb_func_start PrefetchBufferResult
PrefetchBufferResult:
	push	{r4, r5, r6, r7, lr}
	ldr	r4, =REG_TM0CNT
	movs	r5, #0
	str	r5, [r4]
	ldr	r6, =(TIMER_1CLK | TIMER_ENABLE) << 16
	str	r6, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldr	r2, [r4]
	ldrh	r0, [r4]
	str	r5, [r4]
	pop	{r4, r5, r6, r7}
	pop	{r1}
	bx	lr
	.pool
	thumb_func_end PrefetchBufferResult
	.global PrefetchBufferResult_End
PrefetchBufferResult_End:
