gUnknown_84687E0:: @ 84687E0
	.4byte 0x02, 0x10 @ RECEIVE ID(0x10)
	.4byte 0x04, 0x00 @ JUMP TO RECEIVE BUFFER

gUnknown_84687F0::
	.4byte 0x08, 0x00 @ SEND HEADER MAYBE
	.4byte 0x03, 0x00 @ WAIT SEND
	.4byte 0x02, 0x10 @ RECEIVE ID(0x10)
	.4byte 0x04, 0x00 @ JUMP TO RECEIVE BUFFER

gUnknown_8468810::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x0a @ RETURN 0x0a

gUnknown_8468820::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x0b @ RETURN 0x0b

gUnknown_8468830::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x00 @ RETURN 0x00

gUnknown_8468840::
	.4byte 0x02, 0x16 @ RECEIVE ID(0x16)
	.4byte 0x0a, 0x00 @ RECEIVE_TO_SAVE_FILE
	.4byte 0x02, 0x19 @ RECEIVE ID(0x19)
	.4byte 0x11, 0x00 @ RECEIVE_TO_RAM_SCRIPT
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x02 @ RETURN 0x02

gUnknown_8468870::
	.4byte 0x02, 0x17 @ RECEIVE ID(0x17)
	.4byte 0x09, 0x00 @ VALIDATE BUFF3120
	.4byte 0x03, 0x00 @ WAIT SEND
	.4byte 0x02, 0x10 @ RECEIVE ID(0x10)
	.4byte 0x04, 0x00 @ JUMP TO RECEIVE BUFFER

gUnknown_8468898::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x07 @ RETURN 0x07

gUnknown_84688A8::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x03 @ RETURN 0x03

gUnknown_84688B8::
	.4byte 0x0d, 0x00 @ REQUEST PARAMETER
	.4byte 0x0e, 0x00 @ SEND PARAMETER
	.4byte 0x03, 0x00 @ WAIT SEND
	.4byte 0x02, 0x10 @ RECEIVE ID(0x10)
	.4byte 0x04, 0x00 @ JUMP TO RECEIVE BUFFER

gUnknown_84688E0::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x09 @ RETURN 0x09

gUnknown_84688F0::
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x05 @ RETURN 0x05

gUnknown_8468900::
	.4byte 0x02, 0x15 @ RECEIVE ID(0x15)
	.4byte 0x0c, 0x00 @ READ PACKET AND COMPUTE SOMETHING
	.4byte 0x14, 0x00 @ SEND ALL
	.4byte 0x01, 0x0d @ RETURN 0x0d