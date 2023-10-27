	.text			
	.global	_start		

_start:
	li t1, 1		
	li t2, 2		
	add t0, t1, t2

stop:
	j stop			

	.end			
