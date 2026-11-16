using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp1
{
    internal class Person
    {
        private String name;
        private String tel;
        private int num;
        public Person() { }
        public Person(String name, String tel, int num)
        {
            this.name = name;
            this.tel = tel;
            this.num = num;
        }

        // setter, getter
        public String Name { get; set; }
        public String Tel { get; set; }

        public int Num { get; set; }

        public void setName(String name)
        {
            this.name = name;
        }

        public String getName()
        {
            return name;
        }

        public void setTel(String tel)
        {
            this.tel = tel;
        }

        public String getTel()
        {
            return tel;
        }

    }
}
