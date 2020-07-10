#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#define NEW       0
#define PLUS      1
#define PRINTLN   2
#define NAME      3
#define AS_STRING 4
#define LENGTH    5

typedef struct String_ *String;
typedef struct SInteger_ *SInteger;

String newString(char*);
SInteger newSInteger(int);


// Start SInteger Definition

typedef struct SInteger_ {
  Class *class;
  int   value;
} *SInteger;


SObject SInteger_name(SObject this) {
  return (SObject) newString("SInteger");
}

SObject SInteger_println(SObject this) {
  printf("%d\n", ((SInteger) this)->value);
  return this;
}

SObject SInteger_plus(SObject this, SObject that) {
  return (SObject) newSInteger(((SInteger) this)->value + ((SInteger) that)->value);
}

SObject SInteger_asString(SObject this) {
  char* str;
  asprintf (&str, "%i", ((SInteger) this)->value);
  return (SObject) newString(str);
}

Method SIntegerClass(MethodId method) {
  switch ( method ) {
    case NAME:      return SInteger_name ;
    case PLUS:      return (Method) SInteger_plus ;
    case PRINTLN:   return SInteger_println ;
    case AS_STRING: return SInteger_asString ;
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


// Start String Definition

typedef struct String_ {
  Class    *class;
  SInteger length;
  char*    value;
} *String;


SObject String_name(SObject this) {
  return (SObject) newString("String");
}

SObject String_println(SObject this) {
  printf("%s\n", ((String) this)->value);
  return this;
}

SObject String_length(SObject this) {
  return (SObject)((String) this)->length;
}

SObject String_plus(SObject this, SObject that) {
  String sthis = (String) this;
  String sthat = (String) CALL(that, AS_STRING);
  int l1 = sthis->length->value;
  int l2 = sthat->length->value;
  char str[l1 + l2 + 1];
  strcpy(str, sthis->value);
  strcpy(&str[l1], sthat->value);
  return (SObject) newString(str);
}

SObject String_asString(SObject this) {
  return this;
}

Method StringClass(MethodId method) {
  switch ( method ) {
    case NAME:      return String_name ;
    case PLUS:      return (Method) String_plus ;
    case PRINTLN:   return String_println ;
    case AS_STRING: return String_asString ;
    case LENGTH:    return String_length ;
  }
  return no_such_method;
}

String newString(char* str) {
  String obj  = malloc(sizeof(struct String_));
  int len = strlen(str);
  char* buf = malloc(len);
  strcpy(buf, str);
  obj->class  = (Class *) StringClass;
  obj->value  = buf;
  obj->length = newSInteger(len);
  return obj;
}

// End String Definition

int main(void) {
  SInteger i5   = newSInteger(5);
  SInteger i7   = newSInteger(7);
  String   str  = newString("Kevin");
  String   str2 = newString("Greer");

  LOOKUP(i5, NAME);
  CALL(i5, NAME);

  CALL(CALL1(i5, PLUS, i7), PRINTLN);
  CALL(i5, PRINTLN);
  CALL(CALL(i5, AS_STRING), PRINTLN);
  CALL(str, PRINTLN);
  SObject name = CALL1(str, PLUS, str2);
  CALL(name, PRINTLN);
  CALL(CALL(name, NAME), PRINTLN);
  CALL(name, PRINTLN);
  CALL(CALL1(name, PLUS, i5), PRINTLN);
  printf("done.\n");
}
