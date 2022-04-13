	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly

;Section RAM (read write):
	area    maram,data,readwrite
		
		
	include DriverJeuLaser.inc		
	export timer_callback
	export FlagCligno
		
FlagCligno dcw 0
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

timer_callback proc
;	push {lr}
	ldr r0,=FlagCligno
	ldr r1, [r0]
	cmp r1, #0
	bne toto ;if (FlagCligno==0)
	;//then
	; FlagCligno=1
	mov r1, #1
	str r1,[r0]
	;GPIOB_Clear(1);
	mov r0, #1
	b GPIOB_Clear
	;pop {pc}
toto ;//else
	; FlagCligno=0
	mov r1, #0
	str r1, [r0]
	;GPIOB_Set(1);
	mov r0, #1
	b GPIOB_Set
	;pop {pc}
	
	endp



		
		
	END	