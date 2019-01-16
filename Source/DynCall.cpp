#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "DynCall.h"

// Define the "context", a memory area to hold the function calling information
// The header is an uint64_t array:
// nnnnnnnn - Number of parameters to be passed
// aaaaaaaa - Address of the function to call (JMP to)
// 11111111 - Arg1
// 22222222 - Arg2
// ........ - And so on
//

// Define the memory area to hold the calling context
#define MAX_ARGS 32
uint64_t ctx[MAX_ARGS + 2];

// Few test functions to be called by the DynCall framework
void Separator() {
	printf("--------------------------------------\n");
}

int GetArg6(int p1, int p2, float p3, int p4, float p5, int p6) {
	printf("Parms are %d %d %f %d %f %d.\n", p1, p2, p3, p4, p5, p6);
	return(p6);
}

bool AreNumbersEqual(int a, int b) {
	return(a = b);
}

int GetTheMax(int a, int b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

int CallOthers(int a, float b, int c) {
	int r = GetTheMax(a, c);
	float x = b * r;
	return(AreNumbersEqual(r, c));
}

float Divide(float f1, float f2) {
	float result = f1 / f2;
	printf("%f divided by %f is %f.\n", f1, f2, result);
	return result;
}

// Initialize the generic call
void CallInit(uint64_t address) {
	// Prepare the calling context header
	ctx[0] = 0;			// Number of parameters to be passed
	ctx[1] = address;	// Address of the function to call (JMP to)
}

// Push char* onto the context
void CallPushC(char* txt) {
	ctx[2 + ctx[0]++] = (uint64_t)txt;
}

// Push any integer onto the context
void CallPushI(uint64_t val) {
	ctx[2 + ctx[0]++] = val;
}

// Push float onto the context
void CallPushF(float val) {
	ctx[2 + ctx[0]++] = (uint64_t)val;
}

// Call the desired function
uint64_t DynCall_I() {
	return _DynCall_I((uint64_t)&ctx);
}
float DynCall_F() {
	return _DynCall_F((uint64_t)&ctx);
}

int main(void) {
	printf("DynCall v1.1 by Mockba the Borg\n");
	printf("x64 __fastcall generic function caller\n");
	CallInit((uint64_t)Separator);
	DynCall_I();
	//
	printf("Numbers equal: %d.\n", AreNumbersEqual(123, 321));
	CallInit((uint64_t)AreNumbersEqual);
	CallPushI(123);
	CallPushI(321);
	printf("Numbers equal: %d.\n", (int)DynCall_I());
	//
	printf("Bigger is: %d.\n", GetTheMax(123, 321));
	CallInit((uint64_t)GetTheMax);
	CallPushI(123);
	CallPushI(321);
	printf("Bigger is: %d.\n", (int)DynCall_I());
	//
	printf("Result is %d.\n", CallOthers(123, 10.0f, 321));
	CallInit((uint64_t)CallOthers);
	CallPushI(123);
	CallPushF(10.0f);
	CallPushI(321);
	printf("Result is %d.\n", (int)DynCall_I());
	//
	printf("Result is %f.\n", Divide(12.0f, 29.0f));
	CallInit((uint64_t)Divide);
	CallPushF(12.0f);
	CallPushF(29.0f);
	printf("Result is %f.\n", DynCall_F());
	//
	printf("6th is: %d.\n", GetArg6(123, 321, 123.321f, 456, 123.456f, 999));
	CallInit((uint64_t)GetArg6);
	CallPushI(123);
	CallPushI(321);
	CallPushF(123.321f);
	CallPushI(456);
	CallPushF(123.456f);
	CallPushI(999);
	printf("6th is: %d.\n", (int)DynCall_I());
}