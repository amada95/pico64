/* memory_map.ld */

MEMORY
{
	bootrom (rx)	: ORIGIN = 0x00000000, LENGTH = 0x00004000
	osrom	(rx)	: ORIGIN = 0x00004000, LENGTH = 0x0003C000
	ram	(rwx)	: ORIGIN = 0x20000000, LENGTH = 0x00008000
}

__bootrom_start__	= ORIGIN(bootrom);
__bootrom_size__	= LENGTH(bootrom);
__osrom_start__		= ORIGIN(approm);
__osrom_size__		= LENGTH(approm);


/*
*	    0x0 +-----------------------+ 
*               |                       |
*               |      Bootloader       |  <- bootrom
*               |                       |
*	 0x4000 +-----------------------+
*               |                       |
*               |                       |
*               |   Operating System    |  <- osrom + ram
*               |                       |
*               |                       |
*       0x30000 +-----------------------+
*/

