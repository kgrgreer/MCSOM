SInteger newInteger(long value) {
  SInteger o = (SInteger) malloc(sizeof SInteger);
  o.class = CLASS_Integer;
  o.value = value;
  return o;
}
