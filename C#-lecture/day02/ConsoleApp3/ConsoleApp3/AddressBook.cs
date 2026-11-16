using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp3
{
    public class AddressBook
    {
        private Dictionary<int, Person> _members = new Dictionary<int, Person>();

        public int TotalItems => _members.Count;

        public Person this[int index]
        {
            get => _members.ContainsKey(index) ? _members[index] : null;
            set => _members[index] = value;
        }
    }
}
