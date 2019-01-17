// Testbed for the DynCall class

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "DynCall.h"

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

float ReturnF1(float f1) {
	return f1;
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

int main(void) {
	DynCallContext ctx;

	printf("DynCall v1.1 by Mockba the Borg\n");
	printf("x64 __fastcall generic function caller\n");
	ctx.Init(Separator);
	ctx.Call<void>();
	//
	printf("Numbers equal: %d.\n", AreNumbersEqual(123, 321));
	ctx.Init(AreNumbersEqual);
	ctx.Push(123);
	ctx.Push(321);
	printf("Numbers equal: %d.\n", ctx.Call<int>());
	//
	printf("Bigger is: %d.\n", GetTheMax(123, 321));
	ctx.Init(GetTheMax);
	ctx.Push(123);
	ctx.Push(321);
	printf("Bigger is: %d.\n", ctx.Call<int>());
	//
	printf("Returned %f.\n", ReturnF1(-123.456f));
	ctx.Init(ReturnF1);
	ctx.Push(-123.456f);
	printf("Returned %f.\n", ctx.Call<float>());
	//
	printf("Result is %d.\n", CallOthers(123, 10.0f, 321));
	ctx.Init(CallOthers);
	ctx.Push(123);
	ctx.Push(10.0f);
	ctx.Push(321);
	printf("Result is %d.\n", ctx.Call<int>());
	//
	printf("Result is %f.\n", Divide(12.7f, 29.25f));
	ctx.Init(Divide);
	ctx.Push(12.7f);
	ctx.Push(29.25f);
	printf("Result is %f.\n", ctx.Call<float>());
	//
	printf("6th is: %d.\n", GetArg6(123, 321, 123.321f, 456, 123.456f, 999));
	ctx.Init(GetArg6);
	ctx.Push(123);
	ctx.Push(321);
	ctx.Push(123.321f);
	ctx.Push(456);
	ctx.Push(123.456f);
	ctx.Push(999);
	printf("6th is: %d.\n", ctx.Call<int>());
}