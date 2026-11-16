using ConsoleApp7;

Console.WriteLine("Hello, World!");

Parent p1 = new();
Parent p2 = new Child();
Child p3 = new();

p1.f1();
p1.f2();
p2.f1();
p2.f2();
p3.f1();
p3.f2();