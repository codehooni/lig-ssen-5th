using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1
{
    class Person
    {
        public int num;
        public string name;
        public int score;

        public Person(int num, string name, int score)
        {
            this.num = num;
            this.name = name;
            this.score = score;
        }

        public void print()
        {
            Console.WriteLine("num: " + num + ", name: " + name + ", score: " + score);
        }

        public void print2(Person p)
        {
            Console.WriteLine("num: " + num + ", name: " + name + ", score: " + score);
        }

    }
}
