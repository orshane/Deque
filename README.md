# Deque
A deque function for c. This deque header can be used to make fixed size deque.This is useful for games and other purposes. Don't forget to put the library in the include library. 

                                ===Example Usage

#include <stdio.h
===#include <deque.h> //include the library===

===DECLARE_STACK_DEQUE(int ,deque , 10);  //type,name,capacity===

===int main() {===
===//the first word deque should be according to the name===
===deque d; //declare deque as d===
===deque_init(&d); //initialization===
===//also supports other deque functions all of them this is just an example===
===deque_push_back(&d, 10); //push back===
===deque_push_back(&d, 20);===
deque_push_back(&d, 30);
===//print the elements in the deque===
===for (size_t i = 0; i < deque_size(&d); i++) {===
===    int *val = deque_element(&d, i);===
===    if (val) printf("%d ", *val);===
===}===
===printf("\n");===
===   return 0;===
===}===
===
===
