#ifndef MCSOM_H
#define MCSOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

SObject no_such_method(SObject);

#endif
