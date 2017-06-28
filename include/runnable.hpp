#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

struct Runnable {
	virtual bool poll(void) = 0;
	virtual bool run(void) = 0;
	virtual ~Runnable(void) = default;
};

#endif
