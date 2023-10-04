#include <string.h>
#include "Generic.h"

int checkIfRegisterExists(Person *array, int length) {
  int index = 0, found = 0;

  if (length > 0) {
    Person lastCreatedRegister = array[length - 1];
    for (index = 0; index < length; index++) {
      if (lastCreatedRegister.registration == array[index].registration && lastCreatedRegister.registration != 0 &&       
        array[index].registration != 0
      ) {
        found = 1;
        break;
      }
    }
  }

  return found;
}