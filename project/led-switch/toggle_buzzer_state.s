	.global toggle_buzzer_state
	.text

toggle_buzzer_state:
	mov &buzzer_state, r12
	inc r12
	cmp #3, r12
	jl store_state
	clr r12

store_state:
	mov r12, &buzzer_state
	ret
	
