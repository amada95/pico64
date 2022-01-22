/* linker.ld */

ENTRY(boot)
OUTPUT_FORMAT("binary")
SECTIONS
{
	/* offset sections to the end of the MBR record */
	. = 0x7c00;
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
