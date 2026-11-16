using ConsoleApp3;

Console.WriteLine("Hello, World!");

AddressBook ab = new();
ab[0] = new Person("Alex", "010-1234-1234");
ab[1] = new Person("Amy", "010-1234-1234");


Console.WriteLine(ab[0]);
Console.WriteLine(ab[1]);