using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp8
{
    internal abstract class Shape
    {
        public abstract void draw();
    }

    class Circle : Shape
    {
        public override void draw()
        {
            Console.WriteLine("원을 그림");
        }
    }

    class Rectangle : Shape
    {
        public override void draw()
        {
            Console.WriteLine("사각형을 그림");
        }
    }

    class Brush
    {
        public void action(Shape s)
        {
            s.draw();
        }
    }
}
