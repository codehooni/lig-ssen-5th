using ConsoleApp1;

Console.WriteLine("Hello, World!");

Person p = new Person("John", "010-1234-1234", 30);
Console.WriteLine(p.getName());
p.setName("Kan");
Console.WriteLine(p.getName());
p.Name = "Julia";
Console.WriteLine(p.Name);