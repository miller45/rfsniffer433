

#define CARFOB_A 14652642
#define CARFOB_B 14652648
#define CARFOB_C 14652641
#define CARFOB_D 14652644


boolean TryDisplayCarFob(long value) {
  boolean res = false;
  switch (value) {
    case CARFOB_A:
      Serial.print("/ CARFOB_A");
      res = true;
      break;
    case CARFOB_B:
      Serial.print("/ CARFOB_B");
      res = true;
      break;
    case CARFOB_C:
      Serial.print("/ CARFOB_C");
      res = true;
      break;
    case CARFOB_D:
      Serial.print("/ CARFOB_D");
      res = true;
      break;
  }
  return res;
}

