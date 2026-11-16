using ConsoleApp4;

Console.WriteLine("Hello, World!");

Engine e = new();
Car c1 = new(e);
c1.drive();
c1.park();