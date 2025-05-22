# Deque
A deque function for c. This deque header can be used to make fixed size deque.This is useful for games and other purposes. Don't forget to put the library in the include library. 

                                ===Example Usage===
#include <stdio.h>
#include <deque.h>

DECLARE_STACK_DEQUE(int ,deque , 10);

int main() {
deque d;
deque_init(&d);

deque_push_back(&d, 10);
deque_push_back(&d, 20);
deque_push_back(&d, 30);

for (size_t i = 0; i < deque_size(&d); i++) {
    int *val = deque_element(&d, i);
    if (val) printf("%d ", *val);
}
printf("\n");
   return 0;
}
