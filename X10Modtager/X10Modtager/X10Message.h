#ifndef X10MESSAGE_H_
#define X10MESSAGE_H_

struct  X10Message
{
	int unit_;			// 0-31 (0 = all)
	int mode_;			// 0 = PIR-respons, 1 = aktivitetssimulering
	int brightness_;	// 0-100 %
};

#endif /* X10MESSAGE_H_ */