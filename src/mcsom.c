SInteger newInteger(long value) {
  SInteger o = (SInteger) malloc(sizeof SInteger);
  o.class = CLASS_Integer;
  o.value = value;
  return o;
}


SObject MSG(SObject *obj, short method, SObject *arg1) {
  (obj->class)(method)(arg1);
}
