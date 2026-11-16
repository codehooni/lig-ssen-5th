using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp4
{
    public class Engine
    {
        public void start()
        {
            Console.WriteLine("엔진 시작");
        }

        public void stop() { Console.WriteLine("엔진 종료"); }
    }

    public class Car
    {
        private Engine engine;
        public Car(Engine engine) { this.engine = engine; }

        public void drive()
        {
            engine.start();
        }

        public void park()
        {
            engine.stop();
        }
    }
}
