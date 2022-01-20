/* bootloader.ld */

ENTRY(boot)
OUTPUT_FORMAT("binary")
SECTIONS
{
	. = 0x7c00;	// Location of the end of the MBR
	.text :
	{
		*(.boot)
		*(.text)
	}
	.rodata :
	{
		*(.rodata)
	}
	.data :
	{
		*(.data)
	}
	.bss :
	{
		*(.bss)
	}
}
