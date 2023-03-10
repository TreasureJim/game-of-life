#ifndef MACROS_h_
#define MACROS_h_

#define defer(x)    \
	{               \
		result = x; \
		goto defer; \
	}

#endif