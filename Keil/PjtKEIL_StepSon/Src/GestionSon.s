	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
	export SortieSon 
	export CallBackSon	
	extern Son
	extern LongueurSon
	extern PWM_Set_Value_TIM3_Ch3
SortieSon dcw 0
index dcw 0
	export index
	extern FinSon
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici	


CallBackSon proc
	
	ldr r0,=FinSon
	ldr r0, [r0]
	cbnz r0, sortie
	
	push {lr,r4}
	ldr r0,=index
	ldrh r3, [r0]
	ldr r1,=Son
	ldr r2,=SortieSon
	; r4=Son[index]
	ldrsh r4, [r1,r3,lsl #1]
	add r3, #1 ;index ++
	strh r3, [r0]
	
	; r4=r4*720/2^16+360
	mov r1, #720 
	mul r4, r1
	asr r4, #16
	add r4, #360
	strh r4, [r2]
	push {r0}
	mov r0, r4
	bl PWM_Set_Value_TIM3_Ch3
	pop {r0}
	pop {lr,r4}
	
	;Si index==LongueurSon
	ldr r1, =LongueurSon
	ldr r1, [r1]
	ldr r3, [r0]
	cmp r3, r1 ; if (index == LongueurSon)
	bne sortie
	;then index=0
	mov r1, #1
	ldr r2, =FinSon
	str r1, [r2]
	mov r3, #0
	str r3, [r0]
sortie ; else
	bx lr
	
	endp


		
		
	END	