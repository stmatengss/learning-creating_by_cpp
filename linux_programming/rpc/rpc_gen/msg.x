/* msg.x */

program MESSAGEPROG {
	version PRINTMESSAGEVERS {
		int PRINTMESSAGE(string) = 2;
	} = 1;
} = 0x20000001;
