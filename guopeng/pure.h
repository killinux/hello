/*
 * pure.h
 *
 *  Created on: 2011-8-23
 *      Author: kevinguo
 */

#ifndef PURE_H_
#define PURE_H_

#include <iostream>

class pure {
public:
	pure();
	virtual std::string getName() const = 0;
	virtual ~pure();
};

class CollegeFrind : public pure {
public:
	CollegeFrind():pure() {}
	std::string getName() const {
		return "guopeng";
	}
};

class bear {
public:
	bear(int _wei):weight(_wei) {}

	int getWeight() const {
		return weight;
	}
	void Print() {
		printf("in bear::Print()\n");
	}
private:
	int weight;
};

class danger {
public:
	danger(int _num) : leave_num(_num) {}

    int getNum() const {
    	return leave_num;
    }
    void Print() {
        	printf("in danger::Print()\n");
        }
    void Print(int with_arg) {
    	printf("in danger::Print(int with_arg)\n");
    }
private:
	int leave_num;
};

class panda : public bear, public danger {
public:
	panda(int _wei, int _num) : bear(_wei), danger(_num) {}

	void localFunc() {
		printf("in panda::localFunc()\n");
	}
};

class Base {
public:
	Base():m_data(0) {
		// Initlation();
	}
	virtual void Initlation() {
		m_data = 10;
		printf("in Base::Initlation()\n");
	}
	virtual ~Base() {}
private:
	int m_data;
};

class Derived : public Base {
public:
	Derived() {}
    virtual void Initlation() {
    	printf("in Derived::Initlation()\n");
    }
    virtual ~Derived() {}
};


#endif /* PURE_H_ */
