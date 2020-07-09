#include <stdio.h>
#include <stdlib.h>

// Start of Simple Object System

#define LOOKUP(o, m)                ((Class) ((o)->class))(m)
#define CALL(o, m)                  (LOOKUP(o, m))((SObject) (o))
#define CALL1(o, m, a1)             (((Method1) LOOKUP(o, m)))((SObject) (o), (SObject) (a1))
#define CALL2(o, m, a1, a2)         (((Method2) LOOKUP(o, m)))((SObject) (o), (SObject) (a1), (SObject) (a2))
#define CALL3(o, m, a1, a2, a3)     (((Method3) LOOKUP(o, m)))((SObject) (o), (SObject) (a1), (SObject) (a2), (SObject) (a3))
#define CALL4(o, m, a1, a2, a3, a4) (((Method4) LOOKUP(o, m)))((SObject) (o), (SObject) (a1), (SObject) (a2), (SObject) (a3), (SObject) (a4))

typedef short MethodId;
typedef struct SObject_ *SObject;
typedef SObject (*Method )(SObject);
typedef SObject (*Method1)(SObject, SObject);
typedef SObject (*Method2)(SObject, SObject, SObject);
typedef SObject (*Method3)(SObject, SObject, SObject, SObject);
typedef SObject (*Method4)(SObject, SObject, SObject, SObject, SObject);
typedef Method  (*Class)(MethodId);
struct SObject_ { Class *class; };

SObject no_such_method(SObject this) { printf("no such method\n"); return this; }

// End of Simple Object System


#define NEW     0
#define F1      1
#define F2      2
#define F3      3
#define PLUS    4
#define PRINTLN 5
#define NAME    6


SObject f1(SObject this) {
  printf("f1()\n");
  return this;
}

SObject f2(SObject this) {
  printf("f2()\n");
  return this;
}

// Start SInteger Definition

typedef struct SInteger_ {
  Class *class;
  int   value;
} *SInteger;


SInteger newSInteger(int i);

SObject SInteger_name(SObject this) {
  printf("SInteger\n");
  return this;
}

SObject SInteger_println(SObject this) {
  printf("%d\n", ((SInteger) this)->value);
  return this;
}

SObject SInteger_plus(SObject this, SObject that) {
  return (SObject) newSInteger(((SInteger) this)->value + ((SInteger) that)->value);
}

// "Class" Test
Method SIntegerClass(MethodId method) {
  switch ( method ) {
    case NAME:    return SInteger_name ;
    case F1:      return f1 ;
    case PLUS:    return (Method) SInteger_plus ;
    case PRINTLN: return SInteger_println ;
  }
  return no_such_method;
}

SInteger newSInteger(int i) {
  SInteger obj = malloc(sizeof(struct SInteger_));
  obj->class = (Class *) SIntegerClass;
  obj->value = i;
  return obj;
}

// End SInteger Definition

int main(void) {
  SInteger i5 = newSInteger(5);
  SInteger i7 = newSInteger(7);
  LOOKUP(i5, NAME);
  CALL(i5, NAME);
  CALL(CALL1(i5, PLUS, i7), PRINTLN);
}
