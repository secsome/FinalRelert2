using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace FinalRelert2
{
    class CINISection
    {
        public CINISection()
        {
            this.EntityDict = new Dictionary<string, string>();
            this.IndexDict = new Dictionary<string, int>();
        }

        public bool Release()
        {
            this.EntityDict.Clear();
            this.IndexDict.Clear();
            this.IndexCounter = 0;
            return true;
        }

        public void UpdateSectionIndice()
        {
            IndexCounter = 0;

            var sd = new SortedDictionary<int, string>();
            foreach (var pair in IndexDict)
                sd.Add(pair.Value, pair.Key);
            IndexDict.Clear();

            foreach (var pair in sd)
                IndexDict[pair.Value] = ++IndexCounter;
        }

        public void AddEntry(string key,string value)
        {
            EntityDict[key] = value;
            if (IndexDict.ContainsKey(key))
                IndexDict.Remove(key);
            IndexDict[key] = ++IndexCounter;
        }

        private int IndexCounter = 0;

        public Dictionary<string, string> EntityDict { get; private set; }
        public Dictionary<string, int> IndexDict { get; private set; }
    }

    class CINI
    {
        public static CINI Rules = new CINI();
        public static CINI Art = new CINI();
        public static CINI Turtorial = new CINI();
        public static CINI Sound = new CINI();
        public static CINI Eva = new CINI();
        public static CINI Theme = new CINI();
        public static CINI Ai = new CINI();
        public static CINI Temperate = new CINI();
        public static CINI Snow = new CINI();
        public static CINI Urban = new CINI();
        public static CINI NewUrban = new CINI();
        public static CINI Lunar = new CINI();
        public static CINI Desert = new CINI();
        public static CINI FAData = new CINI();
        public static CINI FALanguage = new CINI();
        public static CINI CurrentDocument = new CINI();
        public static CINI CurrentTheater = null;

        public CINI()
        {
            Dict = new Dictionary<string, CINISection>();
            INIPath = string.Empty;
        }

        public bool Release()
        {
            Dict.Clear();
            INIPath = string.Empty;

            return true;
        }

        public bool ParseFile(MemoryStream ms)
        {
            StreamReader sr = new StreamReader(ms);

            string buffer = string.Empty;
            while (!sr.EndOfStream) 
            {
                buffer = sr.ReadLine();
                buffer.Trim();
                if (buffer.Length >= 2 && buffer[0] == '[' && buffer.Contains(']')) 
                    break;
            }

            while (!sr.EndOfStream) 
            {
                int last = buffer.IndexOf(']');
                if (last != -1)
                    buffer = buffer.Substring(1, last - 1);

                CINISection section;
                bool flag = Dict.TryGetValue(buffer, out section);
                if (!flag)
                {
                    section = new CINISection();
                    Dict.Add(buffer, section);
                }

                while (!sr.EndOfStream) 
                {
                    buffer = sr.ReadLine();

                    if (buffer.Length == 0) 
                        continue;

                    if (buffer[0] == '[' && buffer.Contains(']'))
                        break;

                    int comment = buffer.IndexOf(';');
                    if (comment != -1)
                        buffer = buffer.Substring(0, comment);

                    int divider = buffer.IndexOf('=');
                    if (divider == -1)
                        continue;

                    string key = buffer.Substring(0, divider).Trim();
                    string value = buffer.Substring(divider + 1).Trim();

                    section.AddEntry(key, value);
                }
            }

            foreach (var section in Dict)
                section.Value.UpdateSectionIndice();

            return true;
        }

        public bool ParseFile(string path)
        {
            if (!File.Exists(path))
                return false;

            try
            {
                MemoryStream ms = new MemoryStream(File.ReadAllBytes(path));
                return ParseFile(ms);
            }
            catch
            {
                return false;
            }
        }

        private Dictionary<string, CINISection> Dict { get; set; }
        public string INIPath { get; private set; }
    }
}
