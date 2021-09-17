using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinalRelert2
{
    class CINIMethods
    {
        private CINIMethods() => throw new MethodAccessException();

        private static string TryGetString(string pSection, string pKey, Dictionary<string, CINISection> Dict)
        {
            if (!Dict.ContainsKey(pSection))
                return null;
            CINISection itrSection = Dict[pSection];
            if (!itrSection.EntityDict.ContainsKey(pKey))
                return null;
            return itrSection.EntityDict[pKey];
        }

        public static string GetString(string pSection, string pKey, Dictionary<string, CINISection> Dict, string pDefault = null)
        {
            string res = TryGetString(pSection, pKey, Dict);
            if (res != null)
                return res;
            return pDefault;
        }

        public static int GetInteger(string pSection, string pKey, Dictionary<string, CINISection> Dict, int pDefault = 0)
        {
            string res = GetString(pSection, pKey, Dict);
            if (res != null)
                return Convert.ToInt32(res);
            return pDefault;
        }

        public static float GetSingle(string pSection, string pKey, Dictionary<string, CINISection> Dict, float pDefault = 0)
        {
            string res = GetString(pSection, pKey, Dict);
            if (res != null)
                return Convert.ToSingle(res);
            return pDefault;
        }

        public static double GetDouble(string pSection, string pKey, Dictionary<string, CINISection> Dict, double pDefault = 0)
        {
            string res = GetString(pSection, pKey, Dict);
            if (res != null)
                return Convert.ToDouble(res);
            return pDefault;
        }

        public static bool GetBool(string pSection, string pKey, Dictionary<string, CINISection> Dict, bool nDefault = false)
        {
            string res = GetString(pSection, pKey, Dict);
            switch (Convert.ToChar(res))
            {
                case '1':
                case 'T':
                case 'Y':
                    return true;
                case '0':
                case 'F':
                case 'N':
                    return false;
                default:
                    return nDefault;
            }
        }

        public static bool WriteString(string pSection, string pKey, string pValue,Dictionary<string, CINISection> Dict)
        {
            if (pSection == null || pKey == null)
                return false;

            if (Dict.ContainsKey(pSection))
            {
                if (Dict[pSection].EntityDict.ContainsKey(pKey))
                    return false;
                Dict[pSection].EntityDict[pKey] = pValue;
                Dict[pSection].AddEntry(pKey, pValue);
                return true;
            }
            CINISection section = new CINISection();
            section.EntityDict[pKey] = pValue;
            section.AddEntry(pKey, pValue);
            return true;
        }

    }
}
