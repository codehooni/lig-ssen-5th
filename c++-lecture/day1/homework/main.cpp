#include "Person.h"

int main()
{
    PersonService service;
    service.add();
    service.add();
    service.add();
    service.get();
    service.printAll();
    service.edit();
    service.printAll();
    service.del();
    service.del();
    service.printAll();
}