.code16				# generate 16-bit code (to run in real mode)

.section .text			# text/code section
	.global _start		# define entry point

_start:	
	. = _start + 510	# mov 510 bytes forward (end of MBR + Partition Table)
	.byte 0x55		# append boot signature
	.byte 0xaa		# appent booth signature
