using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp7
{
    public class Parent
    {
        public void f1()
        {
            Console.WriteLine("부모 f1()");
        }

        public virtual void f2()
        {
            Console.WriteLine("부모 f2()");
        }
    }

    public class Child : Parent
    {
        public new void f1()
        {
            Console.WriteLine("자식 f1()");
        }

        public override void f2()
        {
            Console.WriteLine("자식 f2()");
        }
    }
}
