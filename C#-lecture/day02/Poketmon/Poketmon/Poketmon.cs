using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Linq;

namespace PoketmonGame
{
    internal abstract class Poketmon
    {
        public string Name {  get; set; }
        public int Level { get; set; }
        public int Hp { get; set; }
        public int Exp { get; set; }

        public bool IsDead { get; set; }

        public Poketmon() { }
        public Poketmon(string name, int level, int hp, int exp)
        {
            Name = name;
            Level = level;
            Hp = hp;
            Exp = exp;
        }

        public void eat() { Hp += 10; if (Hp > 100) Hp = 100; }
        public void sleep() { Hp += 30; if (Hp > 100) Hp = 100; }
        public void exercise() { Hp -= 10; Exp += 20; checkState(); }

        public void play() { Hp -= 5; Exp += 10; checkState(); }

        private void checkState()
        {
            if (Hp <= 0)
            {
                IsDead = true;
                Console.WriteLine(Name + "is Died");
            }
            else if (Exp > 100) {
                Level++;
                Console.WriteLine(Name + "level up~!");
                Exp -= 100;
            }
        }

        public void printState()
        {
            Console.WriteLine(Name + "'s state:");
            Console.WriteLine($"HP: {Hp}");
            Console.WriteLine($"LEVEL: {Level}");
            Console.WriteLine($"EXP: {Exp}");
        }

        public abstract void skill();
    }

    class Pikachu : Poketmon
    {
        public Pikachu(string name, int level, int hp, int exp)
        {
            Name = name;
            Level = level;
            Hp = hp;
            Exp = exp;
        }

        public override void skill()
        {
            Console.WriteLine($"{Name}'s MillionVolts");
        }
    }

    class Squirtle : Poketmon
    {
        public Squirtle(string name, int level, int hp, int exp)
        {
            Name = name;
            Level = level;
            Hp = hp;
            Exp = exp;
        }

        public override void skill()
        {
            Console.WriteLine($"{Name}'s WaterCannon");
        }
    }

    class Bulbasaur : Poketmon
    {
        public Bulbasaur(string name, int level, int hp, int exp)
        {
            Name = name;
            Level = level;
            Hp = hp;
            Exp = exp;
        }

        public override void skill()
        {
            Console.WriteLine($"{Name}'s RazorReaf");
        }
    }
}