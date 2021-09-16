using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinalRelert2
{
    class CINIMethods
    {
        private static string TryGetString(string pSection, string pKey, Dictionary<string, CINISection> Dict)
        {
            if (!Dict.ContainsKey(pSection))
                return null;
            CINISection itrSection = Dict[pSection];
            if (!itrSection.EntityDict.ContainsKey(pKey))
                return null;
            return itrSection.EntityDict[pKey];
        }

        public static string GetString(string pSection, string pKey, Dictionary<string, CINISection> Dict, string pDefault = "")
        {
            string res = TryGetString(pSection, pKey, Dict);
            if (res != null)
                return res;
            return pDefault;
        }
    }
}
