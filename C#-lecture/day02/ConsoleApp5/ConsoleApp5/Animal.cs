using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp5
{
    abstract class Animal
    {
        public string Name { get; set; }
        public Animal(string name)
        {
            Name = name;
            Console.WriteLine("Animal 생성자");
        }
        public void eat()
        {
            Console.WriteLine("밥 먹음");
        }
    }

    class Dog : Animal
    {
        public Dog(string name) : base(name)
        {
            Console.WriteLine("Dog 생성자");
        }
        public new void eat()
        {
            Console.WriteLine("Dog 밥 먹음");
        }
    }
}
