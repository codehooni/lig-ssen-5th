using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp2
{
    internal class Person
    {
        private string name;
        private string tel;
        public Person() { }
        public Person(string name, string tel)
        {
            this.name = name;
            this.tel = tel;
        }

        public void setName(string name)
        {
            this.name = name;
        }

        public string getName()
        {
            return this.name;
        }
        public void setTel(string tel)
        {
            this.tel = tel;
        }
        public string getTel()
        {
            return this.tel;
        }

        public void print()
        {
            Console.WriteLine("name: " + name + ", tel: " + tel);
        }
    }
}
