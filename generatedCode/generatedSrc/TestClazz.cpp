#include ".\generatedHeader\TestClazz.h"
#define STATE__START__STATE 0
#define STATE__mid1 1
#define STATE__start 2
#define STATE__STOP__STATE 3
int __currentState = STATE__START__STATE;
int main(int argc, char** argv) {
while(__currentState != STATE__STOP__STATE) {
	switch(__currentState){
		STATE__mid1:
		STATE__start:
		default: break;
	}
}
}

