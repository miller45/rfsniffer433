

#define OFF1 14013443
#define ON1 14013452
#define OFF2 13988867
#define ON2 13988876
#define OFF3 13982723
#define ON3 13982732


boolean TryDisplayHomeEasy(long value) {
  boolean res = false;
  switch (value) {
    case OFF1:
      Serial.print("/ HEASY OFF1");
      res = true;
      break;
    case ON1:
      Serial.print("/ HEASY ON1");
      res = true;
      break;
    case OFF2:
      Serial.print("/ HEASY OFF2");
      res = true;
      break;
    case ON2:
      Serial.print("/ HEASY ON2");
      res = true;
      break;
    case OFF3:
      Serial.print("/ HEASY OFF3");
      res = true;
      break;
    case ON3:
      Serial.print("/ HEASY ON3");
      res = true;
      break;
  }
  return res;
}

