#ifndef PARA_CALLBACK_H
#define PARA_CALLBACK_H

typedef void (*callback_t) (void *);
void speak(callback_t, void *);

#endif
