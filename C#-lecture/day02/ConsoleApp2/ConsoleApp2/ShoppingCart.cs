using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp2
{
    public class ShoppingCart
    {
        private string[] _items = new string[10];

        public string this[int index]
        {
            get => _items[index];
            set => _items[index] = value;
        }

        public void addItem(string item, int idx)
        {
            _items[idx] = item;
        }
        public string getItem(int idx)
        {
            return _items[idx];
        }
    }
}
