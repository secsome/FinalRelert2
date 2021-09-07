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
        public Dictionary<string, string> EntityDict = new Dictionary<string, string>();
        public Dictionary<string, int> IndexDict = new Dictionary<string, int>();

        void AddEntry(string key,string value)
        {
            EntityDict[key] = value;
            if (IndexDict.ContainsKey(key))
                IndexDict.Remove(key);
            IndexDict[key] = IndexDict.Count;
        }
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

        public bool ParseFile(MemoryStream ms)
        {
            StreamReader sr = new StreamReader(ms);

            string buffer = string.Empty;
            while (!sr.EndOfStream) 
            {
                buffer = sr.ReadLine();
                buffer.Trim();
                if (buffer[0] == '[' && buffer.Contains(']'))
                    break;
            }

            while (!sr.EndOfStream) 
            {
                int last = buffer.IndexOf(']');
                if (last != -1)
                    buffer = buffer.Substring(1, last - 1);

                CINISection section = Dict[buffer];

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
                    buffer.Trim();

                    int divider = buffer.IndexOf('=');
                    if (divider != -1)
                        continue;

                    string key = buffer.Substring(0, divider);
                    
                }
            }

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

        public Dictionary<string, CINISection> Dict;
        public string INIPath;
    }
}
