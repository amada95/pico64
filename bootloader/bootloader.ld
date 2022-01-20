/* bootloader.ld */

ENTRY(boot)
OUTPUT_FORMAT("binary")
SECTIONS
{
	. = 0x7c00; /* offset sections to the end of the MBR record */
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
