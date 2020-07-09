typedef struct SObject_ {
  SClass *class;
} SObject;

typedef struct SInteger_ {
  SClass *class;
  long value;
} SInteger;

typedef struct SClass_ {
  function pointer *lookup;
  SString name;
} SClass;
