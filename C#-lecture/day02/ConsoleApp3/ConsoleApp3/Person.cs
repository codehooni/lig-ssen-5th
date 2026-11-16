using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp3
{
    public class Person
    {
        public String name;
        public String tel;

        public Person(String name, String tel)
        {
            this.name = name;
            this.tel = tel;
        }

        public override string ToString()
        {
            return "name: " + name + ", tel: " + tel;
        }
    }
}
